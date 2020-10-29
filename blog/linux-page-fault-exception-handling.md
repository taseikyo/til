> @Date    : 2020-10-29 15:46:36
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Linux 缺页异常处理

> 原文：https://blog.csdn.net/bin_linux96/article/details/83619973 [Robin.Yin](https://me.csdn.net/bin_linux96) 2018-11-01 14:32:47

## Table of Contents

- [4 mmap 与 malloc 的区别](#4-mmap-与-malloc-的区别)
- [5 缺页中断分析](#5-缺页中断分析)
	- [5.1 私有匿名内存映射](#51-私有匿名内存映射)
- [5.2 文件映射缺页中断](#52-文件映射缺页中断)
	- [5.2.1 只读缺页中断](#521-只读缺页中断)
	- [5.2.2 写时复制缺页处理（加载动态库）](#522-写时复制缺页处理（加载动态库）)
	- [5.2.3 共享文件缺页处理（进程间通信）](#523-共享文件缺页处理（进程间通信）)
- [5.3 交换缺页异常](#53-交换缺页异常)
- [5.4 写时复制缺页（fork）](#54-写时复制缺页（fork）)

1. 如果访问的虚拟地址在进程空间没有对应的 VMA（mmap 和 malloc 可以分配 vma)），则缺页处理失败，程序出现段错误。
2. Linux 把没有映射到文件的映射叫做匿名映射（malloc 和 mmap 的匿名映射）。
3. remap_pfn_range 把内核内存映射到用户空间，一般在设备驱动的 mmap 函数中调用。

```C
int remap_pfn_range(struct vm_area_struct *vma, unsigned long addr,  
					unsigned long pfn, unsigned long size, pgprot_t prot)
```

## 4 mmap 与 malloc 的区别

malloc 只能用来分配匿名私有映射，而 mmap 可以分配四种不同的映射

分配内存小于 128k 时，malloc 分配地址从 start_brk 开始，也就是数据段之后，mmap 起始地址位于 mmap 区

malloc 分配小于 128k 时，由 brk 系统调用实现，而大于 128k，由 mmap 系统调用实现

总之，mmap 功能比 malloc 强大. malloc 是 mmap 的特殊情况。

## 5 缺页中断分析

缺页中断，无非就是建立 GPD->PMD->PTE 到 page 的映射关系，malloc 和 mmap 函数，只是给进程分配了虚拟地址空间（VMA），而并没有分配物理内存，更没有建立对应的页表映射。

缺页中断主要函数: handle_mm_fault-->handle_pte_fault，主要进行物理内存分配，预读文件, 建立页表等, 分四种情况:

1. 私有匿名内存映射
2. 文件映射缺页中断
3. swap 缺省中断
4. 写时复制（COW）缺页中断

### 5.1 私有匿名内存映射

私有的匿名内存映射又可以分为只读缺页，可写缺页中断两种情况，处理函数为 do_anonymous_page，应用场景为 malloc 内存分配

- 只读缺页时，会从 zero page 分配一个 page，并填充具体的 pte 表项
- 可写缺页时，直接从伙伴系统分配一个 page，并填充 pte 表项

```C
static int do_anonymous_page(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pte_t *page_table, pmd_t *pmd,
		unsigned int flags)
{
	/*只读缺页中断，直接分配一个zero page */
	/* Use the zero-page for reads */
	if (!(flags & FAULT_FLAG_WRITE) && !mm_forbids_zeropage(mm)) {
		entry = pte_mkspecial(pfn_pte(my_zero_pfn(address),
						vma->vm_page_prot));
		page_table = pte_offset_map_lock(mm, pmd, address, &ptl);
		goto setpte;//设置pte页表项
	}

	/*可写的缺页中断，直接从伙伴系统分配页面 */
	page = alloc_zeroed_user_highpage_movable(vma, address);
	if (!page)
		goto oom;
	/*设置页面内容有效 */
	__SetPageUptodate(page);
 
　　/*生成pte表项值 */
	entry = mk_pte(page, vma->vm_page_prot);
	if (vma->vm_flags & VM_WRITE)
		entry = pte_mkwrite(pte_mkdirty(entry));
    /*关联匿名页表 */
	page_add_new_anon_rmap(page, vma, address);
	/*添加到lru链表 */
	lru_cache_add_active_or_unevictable(page, vma);
setpte:
	set_pte_at(mm, address, page_table, entry);
	return 0;
}
```

## 5.2 文件映射缺页中断

可以分为三种情况，函数 do_fault 处理这三种情况：

1. 只读缺页中断（mmap 读取文件）
2. 写时复制缺页中断（加载动态库）
3. 共享缺页中断（进程通信）

```C
static int do_fault(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pte_t *page_table, pmd_t *pmd,
		unsigned int flags, pte_t orig_pte)
{
	pgoff_t pgoff = (((address & PAGE_MASK)
			- vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
 
	pte_unmap(page_table);
	/*可读缺页中断*/
	if (!(flags & FAULT_FLAG_WRITE))
		return do_read_fault(mm, vma, address, pmd, pgoff, flags,orig_pte);
	/*写时复制缺页中断 */
　　if (!(vma->vm_flags & VM_SHARED))
		return do_cow_fault(mm, vma, address, pmd, pgoff, flags,orig_pte);
    /*共享内存缺页中断 */
	return do_shared_fault(mm, vma, address, pmd, pgoff, flags, orig_pte);
}
```

### 5.2.1 只读缺页中断

先介绍 `struct vm_operations_struct *vm_ops` 的三个重要函数 fault 和 map_pages，page_mkwrite

```C
struct vm_operations_struct {

	/* 从 page cache 或者伙伴系统分配页面，进行文件预读 (readahead), 并填充页面内容 */
	int (*fault)(struct vm_area_struct *vma, struct vm_fault *vmf);

	/* 从 page cache 获取页面，并建立页表映射 */
	void (*map_pages)(struct vm_area_struct *vma, struct vm_fault *vmf);

	/* notification that a previously read-only page is about to become
	* writable, if an error is returned it will cause a SIGBUS */

	/* 标记页面可写，并回写页面内容到磁盘 */
	int (*page_mkwrite)(struct vm_area_struct *vma, struct vm_fault *vmf);
}
```

文件映射的缺页异常处理，基本就是调用这三个函数，进程页面分配和文件预读，页表映射

```C
static int do_read_fault(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pmd_t *pmd,
		pgoff_t pgoff, unsigned int flags, pte_t orig_pte)
{
	
	if (vma->vm_ops->map_pages && fault_around_bytes >> PAGE_SHIFT > 1) {
		pte = pte_offset_map_lock(mm, pmd, address, &ptl);
		/*do_fault_around函数会预先映射缺页页面周围的16页面，这样可以减少缺页中断次数 */
        do_fault_around(vma, address, pte, pgoff, flags);
		if (!pte_same(*pte, orig_pte))
			goto unlock_out;
		pte_unmap_unlock(pte, ptl);
	}
	/*do_fault函数主要调用文件系统对应的fault函数，从page cache分配页面(如果page cache没有页面缓存，则从伙伴系统分配)，从文件预读，并填充页面 */
	ret = __do_fault(vma, address, pgoff, flags, NULL, &fault_page);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		return ret;
	/*建立页表 */
	pte = pte_offset_map_lock(mm, pmd, address, &ptl);
	do_set_pte(vma, address, fault_page, pte, false, false);
	return ret;
}
```

### 5.2.2 写时复制缺页处理（加载动态库）

处理函数 do_cow_fault 主要分配 new page，并从 old page 复制内容到 new page，并且会调用 `__do_fault` 进行文件预读。

### 5.2.3 共享文件缺页处理（进程间通信）

处理函数 do_shared_fault 主要调用 `__do_fault` 函数预读文件，并回写内容到磁盘。

## 5.3 交换缺页异常

内存页面被换出到磁盘，处理函数 do_swap_page 把页面内容从磁盘换回内存。

## 5.4 写时复制缺页（fork）

这里的写时复制缺页异常，主要用于处理子父进程（fork）的缺页。与文件的写时复制缺页处理和应用场景不一样。函数 do_wp_page 处理这种异常。
