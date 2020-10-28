> @Date    : 2020-10-28 20:20:06
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Linux 内存管理（7）VMA 操作

> 原文 https://www.cnblogs.com/arnoldlu/p/8329279.html 2018-01-27 21:56

专题：[Linux 内存管理专题](linux-memory-management-topics-0.md)

关键词：VMA、vm_area_struct、查找/插入/合并 VMA、红黑树。

## Table of Contents

- [1 数据结构](#1-数据结构)
- [2 查找 VMA](#2-查找-vma)
- [3 插入 VMA](#3-插入-vma)
- [4 合并 VMA](#4-合并-vma)
- [5 红黑树例子](#5-红黑树例子)

用户进程可以拥有 3GB 大小的空间，远大于物理内存，那么这些用户进程的虚拟地址空间是如何管理的呢？

malloc() 或 mmap() 操作都会要求在虚拟地址空间中分配内存块，但这些内存在物理上往往都是离散的。

这些进程地址空间在内核中使用 struct vm_area_struct 数据结构来描述，简称 VMA，也被称为进程地址空间或进程线性区。

## 1 数据结构

struct vm_area_struct 可以说是 VMA 的描述符，在创建之后会插入到 mm->mm_rb 红黑树和 mm->mmap 链表中。

```C
/*
 * This struct defines a memory VMM memory area. There is one of these
 * per VM-area/task.  A VM area is any part of the process virtual memory
 * space that has a special rule for the page-fault handlers (ie a shared
 * library, the executable area etc).
 */
struct vm_area_struct {
    /* The first cache line has the info for VMA tree walking. */

    unsigned long vm_start;        /* Our start address within vm_mm. */ // VMA在进程地址空间的起始结束地址
    unsigned long vm_end;        /* The first byte after our end address
                       within vm_mm. */

    /* linked list of VM areas per task, sorted by address */
    struct vm_area_struct *vm_next, *vm_prev; // VMA链表的前后成员

    struct rb_node vm_rb; // VMA作为一个节点加入到红黑树中，每个进程的mm_struct中都有一个红黑树mm->mm_rb。

    /*
     * Largest free memory gap in bytes to the left of this VMA.
     * Either between this VMA and vma->vm_prev, or between one of the
     * VMAs below us in the VMA rbtree and its ->vm_prev. This helps
     * get_unmapped_area find a free area of the right size.
     */
    unsigned long rb_subtree_gap;

    /* Second cache line starts here. */

    struct mm_struct *vm_mm;    /* The address space we belong to. */ // 指向VMA所属进程的struct mm_struct结构。
    pgprot_t vm_page_prot;        /* Access permissions of this VMA. */ // VMA访问权限
    unsigned long vm_flags;        /* Flags, see mm.h. */ // VMA标志位

    /*
     * For areas with an address space and backing store,
     * linkage into the address_space->i_mmap interval tree.
     */
    struct {
        struct rb_node rb;
        unsigned long rb_subtree_last;
    } shared;

    /*
     * A file's MAP_PRIVATE vma can be in both i_mmap tree and anon_vma
     * list, after a COW of one of the file pages.    A MAP_SHARED vma
     * can only be in the i_mmap tree.  An anonymous MAP_PRIVATE, stack
     * or brk vma (with NULL file) can only be in an anon_vma list.
     */
    struct list_head anon_vma_chain; /* Serialized by mmap_sem & // 用于管理RMAP反向映射。
                      * page_table_lock */
    struct anon_vma *anon_vma;    /* Serialized by page_table_lock */ // 用于管理RMAP反向映射。

    /* Function pointers to deal with this struct. */
    const struct vm_operations_struct *vm_ops; // VMA操作函数合集，常用于文件映射。

    /* Information about our backing store: */
    unsigned long vm_pgoff;        /* Offset (within vm_file) in PAGE_SIZE-指定文件映射的偏移量，单位是页面。
                       units, *not* PAGE_CACHE_SIZE */
    struct file *vm_file;        /* File we map to (can be NULL). */ // 描述一个被映射的文件。
    void *vm_private_data;        /* was vm_pte (shared mem) */

#ifndef CONFIG_MMU
    struct vm_region *vm_region;    /* NOMMU mapping region */
#endif
#ifdef CONFIG_NUMA
    struct mempolicy *vm_policy;    /* NUMA policy for the VMA */
#endif
}
```

struct  mm_struct 是描述进程内存管理的核心数据结构，VMA 属于进程内存区域。在 mm_struct 中通过 mmap 链表和 mm_rb 对 vm_area_struct 进行管理。

```C
struct mm_struct {
    struct vm_area_struct *mmap;        /* list of VMAs */ // 单链表，按起始地址递增的方式插入，所有的VMA都连接到此链表中。链表头是mm_struct->mmap。
    struct rb_root mm_rb; // 所有的VMA按照地址插入mm_struct->mm_rb红黑树中，mm_struct->mm_rb是根节点，每个进程都有一个红黑树。
...
}
```

## 2 查找 VMA

```C
/* Look up the first VMA which satisfies  addr < vm_end,  NULL if none. */
struct vm_area_struct *find_vma(struct mm_struct *mm, unsigned long addr)
{
    struct rb_node *rb_node;
    struct vm_area_struct *vma;

    /* Check the cache first. */
    vma = vmacache_find(mm, addr);
    if (likely(vma))
        return vma;

    rb_node = mm->mm_rb.rb_node;
    vma = NULL;

    while (rb_node) {
        struct vm_area_struct *tmp;

        tmp = rb_entry(rb_node, struct vm_area_struct, vm_rb);

        if (tmp->vm_end > addr) {
            vma = tmp;
            if (tmp->vm_start <= addr)
                break;
            rb_node = rb_node->rb_left;
        } else
            rb_node = rb_node->rb_right;
    }

    if (vma)
        vmacache_update(addr, vma);
    return vma;
}

struct vm_area_struct *vmacache_find(struct mm_struct *mm, unsigned long addr)
{
    int i;

    if (!vmacache_valid(mm))
        return NULL;

    count_vm_vmacache_event(VMACACHE_FIND_CALLS);

    for (i = 0; i < VMACACHE_SIZE; i++) {
        struct vm_area_struct *vma = current->vmacache[i];

        if (!vma)
            continue;
        if (WARN_ON_ONCE(vma->vm_mm != mm))
            break;
        if (vma->vm_start <= addr && vma->vm_end > addr) {
            count_vm_vmacache_event(VMACACHE_FIND_HITS);
            return vma;
        }
    }
    return NULL;
}

void vmacache_update(unsigned long addr, struct vm_area_struct *newvma)
{
    if (vmacache_valid_mm(newvma->vm_mm))
        current->vmacache[VMACACHE_HASH(addr)] = newvma;
}
```

## 3 插入 VMA

```C
int insert_vm_struct(struct mm_struct *mm, struct vm_area_struct *vma)
{
    struct vm_area_struct *prev;
    struct rb_node **rb_link, *rb_parent;

    /*
     * The vm_pgoff of a purely anonymous vma should be irrelevant
     * until its first write fault, when page's anon_vma and index
     * are set.  But now set the vm_pgoff it will almost certainly
     * end up with (unless mremap moves it elsewhere before that
     * first wfault), so /proc/pid/maps tells a consistent story.
     *
     * By setting it to reflect the virtual start address of the
     * vma, merges and splits can happen in a seamless way, just
     * using the existing file pgoff checks and manipulations.
     * Similarly in do_mmap_pgoff and in do_brk.
     */
    if (!vma->vm_file) {
        BUG_ON(vma->anon_vma);
        vma->vm_pgoff = vma->vm_start >> PAGE_SHIFT;
    }
    if (find_vma_links(mm, vma->vm_start, vma->vm_end,
               &prev, &rb_link, &rb_parent))
        return -ENOMEM;
    if ((vma->vm_flags & VM_ACCOUNT) &&
         security_vm_enough_memory_mm(mm, vma_pages(vma)))
        return -ENOMEM;

    vma_link(mm, vma, prev, rb_link, rb_parent);
    return 0;
}
```

```C
static int find_vma_links(struct mm_struct *mm, unsigned long addr,
        unsigned long end, struct vm_area_struct **pprev,
        struct rb_node ***rb_link, struct rb_node **rb_parent)
{
    struct rb_node **__rb_link, *__rb_parent, *rb_prev;

    __rb_link = &mm->mm_rb.rb_node;
    rb_prev = __rb_parent = NULL;

    while (*__rb_link) {
        struct vm_area_struct *vma_tmp;

        __rb_parent = *__rb_link;
        vma_tmp = rb_entry(__rb_parent, struct vm_area_struct, vm_rb);

        if (vma_tmp->vm_end > addr) {
            /* Fail if an existing vma overlaps the area */
            if (vma_tmp->vm_start < end)
                return -ENOMEM;
            __rb_link = &__rb_parent->rb_left;
        } else {
            rb_prev = __rb_parent;
            __rb_link = &__rb_parent->rb_right;
        }
    }

    *pprev = NULL;
    if (rb_prev)
        *pprev = rb_entry(rb_prev, struct vm_area_struct, vm_rb);
    *rb_link = __rb_link;
    *rb_parent = __rb_parent;
    return 0;
}
```

```C
static void vma_link(struct mm_struct *mm, struct vm_area_struct *vma,
            struct vm_area_struct *prev, struct rb_node **rb_link,
            struct rb_node *rb_parent)
{
    struct address_space *mapping = NULL;

    if (vma->vm_file) {
        mapping = vma->vm_file->f_mapping;
        i_mmap_lock_write(mapping);
    }

    __vma_link(mm, vma, prev, rb_link, rb_parent);
    __vma_link_file(vma);

    if (mapping)
        i_mmap_unlock_write(mapping);

    mm->map_count++;
    validate_mm(mm);
}
```

## 4 合并 VMA

```C
/*
 * Given a mapping request (addr,end,vm_flags,file,pgoff), figure out
 * whether that can be merged with its predecessor or its successor.
 * Or both (it neatly fills a hole).
 *
 * In most cases - when called for mmap, brk or mremap - [addr,end) is
 * certain not to be mapped by the time vma_merge is called; but when
 * called for mprotect, it is certain to be already mapped (either at
 * an offset within prev, or at the start of next), and the flags of
 * this area are about to be changed to vm_flags - and the no-change
 * case has already been eliminated.
 *
 * The following mprotect cases have to be considered, where AAAA is
 * the area passed down from mprotect_fixup, never extending beyond one
 * vma, PPPPPP is the prev vma specified, and NNNNNN the next vma after:
 *
 *     AAAA             AAAA                AAAA          AAAA
 *    PPPPPPNNNNNN    PPPPPPNNNNNN    PPPPPPNNNNNN    PPPPNNNNXXXX
 *    cannot merge    might become    might become    might become
 *                    PPNNNNNNNNNN    PPPPPPPPPPNN    PPPPPPPPPPPP 6 or
 *    mmap, brk or    case 4 below    case 5 below    PPPPPPPPXXXX 7 or
 *    mremap move:                                    PPPPNNNNNNNN 8
 *        AAAA
 *    PPPP    NNNN    PPPPPPPPPPPP    PPPPPPPPNNNN    PPPPNNNNNNNN
 *    might become    case 1 below    case 2 below    case 3 below
 *
 * Odd one out? Case 8, because it extends NNNN but needs flags of XXXX:
 * mprotect_fixup updates vm_flags & vm_page_prot on successful return.
 */
struct vm_area_struct *vma_merge(struct mm_struct *mm,
            struct vm_area_struct *prev, unsigned long addr,
            unsigned long end, unsigned long vm_flags,
            struct anon_vma *anon_vma, struct file *file,
            pgoff_t pgoff, struct mempolicy *policy)
{
    pgoff_t pglen = (end - addr) >> PAGE_SHIFT;
    struct vm_area_struct *area, *next;
    int err;

    /*
     * We later require that vma->vm_flags == vm_flags,
     * so this tests vma->vm_flags & VM_SPECIAL, too.
     */
    if (vm_flags & VM_SPECIAL)
        return NULL;

    if (prev)
        next = prev->vm_next;
    else
        next = mm->mmap;
    area = next;
    if (next && next->vm_end == end)        /* cases 6, 7, 8 */
        next = next->vm_next;

    /*
     * Can it merge with the predecessor?
     */
    if (prev && prev->vm_end == addr &&
            mpol_equal(vma_policy(prev), policy) &&
            can_vma_merge_after(prev, vm_flags,
                        anon_vma, file, pgoff)) {
        /*
         * OK, it can.  Can we now merge in the successor as well?
         */
        if (next && end == next->vm_start &&
                mpol_equal(policy, vma_policy(next)) &&
                can_vma_merge_before(next, vm_flags,
                    anon_vma, file, pgoff+pglen) &&
                is_mergeable_anon_vma(prev->anon_vma,
                              next->anon_vma, NULL)) {
                            /* cases 1, 6 */
            err = vma_adjust(prev, prev->vm_start,
                next->vm_end, prev->vm_pgoff, NULL);
        } else                    /* cases 2, 5, 7 */
            err = vma_adjust(prev, prev->vm_start,
                end, prev->vm_pgoff, NULL);
        if (err)
            return NULL;
        khugepaged_enter_vma_merge(prev, vm_flags);
        return prev;
    }

    /*
     * Can this new request be merged in front of next?
     */
    if (next && end == next->vm_start &&
            mpol_equal(policy, vma_policy(next)) &&
            can_vma_merge_before(next, vm_flags,
                    anon_vma, file, pgoff+pglen)) {
        if (prev && addr < prev->vm_end)    /* case 4 */
            err = vma_adjust(prev, prev->vm_start,
                addr, prev->vm_pgoff, NULL);
        else                    /* cases 3, 8 */
            err = vma_adjust(area, addr, next->vm_end,
                next->vm_pgoff - pglen, NULL);
        if (err)
            return NULL;
        khugepaged_enter_vma_merge(area, vm_flags);
        return area;
    }

    return NULL;
}
```

## 5 红黑树例子
