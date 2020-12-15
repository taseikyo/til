> @Date    : 2020-10-27 17:45:06
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Linux 内存管理（15）页面迁移

> 原文：https://www.cnblogs.com/arnoldlu/p/8335524.html 2018-02-10 10:42

专题：[Linux 内存管理专题](linux-memory-management-topics-0.md)

关键词：RMAP、页面迁移。

相关章节：[反向映射 RMAP](linux-memory-management-topics-12.md)、[内存规整](linux-memory-management-topics-16.md)。

## Table of Contents

- [1 migrate_pages 系统调用](#1-migrate_pages-系统调用)
- [2 migrate_pages](#2-migrate_pages)

页面迁移的初衷是为 NUMA 系统提供一种将进程迁移到任意内存节点的能力，后来内存规整和内存热插拔场景都使用了此功能。

页面迁移将就页面内容，迁移到新的页面。

需要分配新页面，将旧页面内容拷贝到新页面；然后利用 RAMP 技术解除旧页面的映射关系，并将映射关系映射到新页面。

## 1 migrate_pages 系统调用

Linux 提供了 migrate_pages 系统调用，从 old_nodes 中获取原内存节点，从 new_nodes 中获取目的内存节点；然后将当前进程的 mm_struct 作为参数，调用 do_migrate_pages 进行迁移操作。

```C
SYSCALL_DEFINE4(migrate_pages, pid_t, pid, unsigned long, maxnode,
        const unsigned long __user *, old_nodes,
        const unsigned long __user *, new_nodes)
{
    const struct cred *cred = current_cred(), *tcred;
    struct mm_struct *mm = NULL;
    struct task_struct *task;
    nodemask_t task_nodes;
    int err;
    nodemask_t *old;
    nodemask_t *new;
    NODEMASK_SCRATCH(scratch);

    if (!scratch)
        return -ENOMEM;

    old = &scratch->mask1;
    new = &scratch->mask2;

    err = get_nodes(old, old_nodes, maxnode);
    if (err)
        goto out;

    err = get_nodes(new, new_nodes, maxnode);
    if (err)
        goto out;
...
    mm = get_task_mm(task);
    put_task_struct(task);

    if (!mm) {
        err = -EINVAL;
        goto out;
    }

    err = do_migrate_pages(mm, old, new,
        capable(CAP_SYS_NICE) ? MPOL_MF_MOVE_ALL : MPOL_MF_MOVE);
...
}
```

do_migrate_pages 最终将迁移工作交给 migrate_pages 来处理：do_migrate_pages-->migrate_to_node-->migrate_pages。

## 2. migrate_pages

```
migrate_pages-------------------------------------页面迁移核心函数
    unmap_and_move
        get_new_page------------------------------分配新页面
        __unmap_and_move--------------------------迁移页面到新页面
            move_to_new_page
                page_mapping----------------------找到页面对应的地址空间
                migrate_page----------------------将旧页面的相关信息迁移到新页面
                    migrate_page_copy
                remove_migration_ptes-------------利用方向映射找到映射旧页面的每个PTE
                    remove_migration_pte----------处理其中一个虚拟地址
```

from 表示将要迁移的页面链表，get_new_page 是内存函数指针，put_new_page 是迁移失败时释放目标页面的函数指针，private 是传递给 get_new_page 的参数，mode 是迁移模式，reason 表示迁移原因。

```C
int migrate_pages(struct list_head *from, new_page_t get_new_page,
        free_page_t put_new_page, unsigned long private,
        enum migrate_mode mode, int reason)
{
    int retry = 1;
    int nr_failed = 0;
    int nr_succeeded = 0;
    int pass = 0;
    struct page *page;
    struct page *page2;
    int swapwrite = current->flags & PF_SWAPWRITE;
    int rc;

    if (!swapwrite)
        current->flags |= PF_SWAPWRITE;
    // 【尝试10次，从from摘取一个页面，调用unmap_and_move()函数进行页迁移，返回MIGRATEPAGE_SUCCESS表示页迁移成功。】
    for(pass = 0; pass < 10 && retry; pass++) { 
        retry = 0;

        list_for_each_entry_safe(page, page2, from, lru) {
            cond_resched();

            if (PageHuge(page))
                rc = unmap_and_move_huge_page(get_new_page,
                        put_new_page, private, page,
                        pass > 2, mode);
            else
                rc = unmap_and_move(get_new_page, put_new_page,
                        private, page, pass > 2, mode);

            switch(rc) {
            case -ENOMEM:
                goto out;
            case -EAGAIN:
                retry++;
                break;
            case MIGRATEPAGE_SUCCESS:
                nr_succeeded++;
                break;
            default:
                /*
                 * Permanent failure (-EBUSY, -ENOSYS, etc.):
                 * unlike -EAGAIN case, the failed page is
                 * removed from migration page list and not
                 * retried in the next outer loop.
                 */
                nr_failed++;
                break;
            }
        }
    }
    rc = nr_failed + retry;
out:
    if (nr_succeeded)
        count_vm_events(PGMIGRATE_SUCCESS, nr_succeeded);
    if (nr_failed)
        count_vm_events(PGMIGRATE_FAIL, nr_failed);
    trace_mm_migrate_pages(nr_succeeded, nr_failed, mode, reason);

    if (!swapwrite)
        current->flags &= ~PF_SWAPWRITE;

    return rc;
}
```

newpage 是由 `get_new_page` 分配的页面，`__unmap_and_move` 尝试迁移页面 page 到新分配的页面 newpage。

`__unmap_new_page` 被 `unmap_new_page` 调用，其中 force 在尝试次数超过 2 时，就被置 1。


```C
static int __unmap_and_move(struct page *page, struct page *newpage,
                int force, enum migrate_mode mode)
{
    int rc = -EAGAIN;
    int page_was_mapped = 0;
    struct anon_vma *anon_vma = NULL;
    // 【尝试给页面加锁，返回false表示已经有别的进程给page枷锁，返回true表示当前进程可以成功获取锁。】
    if (!trylock_page(page)) {
        if (!force || mode == MIGRATE_ASYNC) // 【加锁失败，且强制迁移或异步模式，则忽略这个页面。】
            goto out;

        /*
         * It's not safe for direct compaction to call lock_page.
         * For example, during page readahead pages are added locked
         * to the LRU. Later, when the IO completes the pages are
         * marked uptodate and unlocked. However, the queueing
         * could be merging multiple pages for one bio (e.g.
         * mpage_readpages). If an allocation happens for the
         * second or third page, the process can end up locking
         * the same page twice and deadlocking. Rather than
         * trying to be clever about what pages can be locked,
         * avoid the use of lock_page for direct compaction
         * altogether.
         */
        if (current->flags & PF_MEMALLOC) // 【可能在直接内存压缩路径上，睡眠等待页面锁是不安全的，忽略此页面。】
            goto out;

        lock_page(page);
    }

    if (PageWriteback(page)) {
        /*
         * Only in the case of a full synchronous migration is it
         * necessary to wait for PageWriteback. In the async case,
         * the retry loop is too short and in the sync-light case,
         * the overhead of stalling is too much
         */
        if (mode != MIGRATE_SYNC) {
            rc = -EBUSY;
            goto out_unlock;
        }
        if (!force)
            goto out_unlock;
        wait_on_page_writeback(page);
    }
    /*
     * By try_to_unmap(), page->mapcount goes down to 0 here. In this case,
     * we cannot notice that anon_vma is freed while we migrates a page.
     * This get_anon_vma() delays freeing anon_vma pointer until the end
     * of migration. File cache pages are no problem because of page_lock()
     * File Caches may use write_page() or lock_page() in migration, then,
     * just care Anon page here.
     */
    if (PageAnon(page) && !PageKsm(page)) {
        /*
         * Only page_lock_anon_vma_read() understands the subtleties of
         * getting a hold on an anon_vma from outside one of its mms.
         */
        anon_vma = page_get_anon_vma(page);
        if (anon_vma) {
            /*
             * Anon page
             */
        } else if (PageSwapCache(page)) {
            /*
             * We cannot be sure that the anon_vma of an unmapped
             * swapcache page is safe to use because we don't
             * know in advance if the VMA that this page belonged
             * to still exists. If the VMA and others sharing the
             * data have been freed, then the anon_vma could
             * already be invalid.
             *
             * To avoid this possibility, swapcache pages get
             * migrated but are not remapped when migration
             * completes
             */
        } else {
            goto out_unlock;
        }
    }

    if (unlikely(isolated_balloon_page(page))) {
        /*
         * A ballooned page does not need any special attention from
         * physical to virtual reverse mapping procedures.
         * Skip any attempt to unmap PTEs or to remap swap cache,
         * in order to avoid burning cycles at rmap level, and perform
         * the page migration right away (proteced by page lock).
         */
        rc = balloon_page_migrate(newpage, page, mode);
        goto out_unlock;
    }

    /*
     * Corner case handling:
     * 1. When a new swap-cache page is read into, it is added to the LRU
     * and treated as swapcache but it has no rmap yet.
     * Calling try_to_unmap() against a page->mapping==NULL page will
     * trigger a BUG.  So handle it here.
     * 2. An orphaned page (see truncate_complete_page) might have
     * fs-private metadata. The page can be picked up due to memory
     * offlining.  Everywhere else except page reclaim, the page is
     * invisible to the vm, so the page can not be migrated.  So try to
     * free the metadata, so the page can be freed.
     */
    if (!page->mapping) {
        VM_BUG_ON_PAGE(PageAnon(page), page);
        if (page_has_private(page)) {
            try_to_free_buffers(page);
            goto out_unlock;
        }
        goto skip_unmap;
    }

    /* Establish migration ptes or remove ptes */
    if (page_mapped(page)) { // 【有 pte 映射的页面，调用 try_to_unmap() 解除页面所有映射】
        try_to_unmap(page,
            TTU_MIGRATION|TTU_IGNORE_MLOCK|TTU_IGNORE_ACCESS);
        page_was_mapped = 1;
    }

skip_unmap:
    if (!page_mapped(page)) // 【已经解除完所有映射的页面，将页面迁移到新分配的页面newpage。】
        rc = move_to_new_page(newpage, page, page_was_mapped, mode);

    if (rc && page_was_mapped) // 【rc 不为 0 表示迁移页面失败，调用 remove_migration_ptes() 删掉迁移的 pte。】
        remove_migration_ptes(page, page);

    /* Drop an anon_vma reference if we took one */
    if (anon_vma)
        put_anon_vma(anon_vma);

out_unlock:
    unlock_page(page);
out:
    return rc;
}
```

move_to_new_page 是将 page 内容迁移到 newpage，mode 是迁移模式异步、或者同步。

```C
static int move_to_new_page(struct page *newpage, struct page *page,
                int page_was_mapped, enum migrate_mode mode)
{
    struct address_space *mapping;
    int rc;

    /*
     * Block others from accessing the page when we get around to
     * establishing additional references. We are the only one
     * holding a reference to the new page at this point.
     */
    if (!trylock_page(newpage)) // 【持锁失败，说明可能被其它进程加锁，BUG进行处理。】
        BUG();

    /* Prepare mapping for the new page.*/
    newpage->index = page->index;
    newpage->mapping = page->mapping;
    if (PageSwapBacked(page))
        SetPageSwapBacked(newpage);
    // 【检查当前页面你是否被映射。如果page属于slab或是匿名页面，返回为空。SWAP则返回swap_address_space空间；其余page cache直接返回page->mapping。】
    mapping = page_mapping(page); 
    if (!mapping)
        rc = migrate_page(mapping, newpage, page, mode); // 【slab或者匿名页面调用migrate_page()将旧页面相关信息迁移到新页面。】
    else if (mapping->a_ops->migratepage)
        /*
         * Most pages have a mapping and most filesystems provide a
         * migratepage callback. Anonymous pages are part of swap
         * space which also has its own migratepage callback. This
         * is the most common path for page migration.
         */
        rc = mapping->a_ops->migratepage(mapping,
                        newpage, page, mode); // 【有mapping的情况，调用migratepage函数进行迁移。】
    else
        rc = fallback_migrate_page(mapping, newpage, page, mode);

    if (rc != MIGRATEPAGE_SUCCESS) {
        newpage->mapping = NULL;
    } else {
        mem_cgroup_migrate(page, newpage, false);
        if (page_was_mapped)
            remove_migration_ptes(page, newpage);
        page->mapping = NULL;
    }

    unlock_page(newpage);

    return rc;
}
```

migrate_pte 函数进行页面复制工作。

```C
int migrate_page(struct address_space *mapping,
        struct page *newpage, struct page *page,
        enum migrate_mode mode)
{
    int rc;

    BUG_ON(PageWriteback(page));    /* Writeback must be complete */

    rc = migrate_page_move_mapping(mapping, newpage, page, NULL, mode, 0); // 【对于匿名页面来说，什么也不做直接返回。】

    if (rc != MIGRATEPAGE_SUCCESS)
        return rc;

    migrate_page_copy(newpage, page); // 【把页面page复制到新页面newpage中。】
    return MIGRATEPAGE_SUCCESS;
}
```

remove_migration_ptes 利用 RMAP 反向映射系统找到映射旧页面的每个 pte，然后和新页面建立新的映射关系。

```C
static void remove_migration_ptes(struct page *old, struct page *new)
{
    struct rmap_walk_control rwc = {
        .rmap_one = remove_migration_pte,
        .arg = old,
    };

    rmap_walk(new, &rwc);
}

static int remove_migration_pte(struct page *new, struct vm_area_struct *vma,
                 unsigned long addr, void *old)
{
    struct mm_struct *mm = vma->vm_mm;
    swp_entry_t entry;
    pmd_t *pmd;
    pte_t *ptep, pte;
     spinlock_t *ptl;

    if (unlikely(PageHuge(new))) {
        ptep = huge_pte_offset(mm, addr);
        if (!ptep)
            goto out;
        ptl = huge_pte_lockptr(hstate_vma(vma), mm, ptep);
    } else {
        pmd = mm_find_pmd(mm, addr);
        if (!pmd)
            goto out;

        ptep = pte_offset_map(pmd, addr); // 【通过mm和addr找到对应页表项pte。】

        /*
         * Peek to check is_swap_pte() before taking ptlock?  No, we
         * can race mremap's move_ptes(), which skips anon_vma lock.
         */

        ptl = pte_lockptr(mm, pmd);
    }

     spin_lock(ptl);
    pte = *ptep;
    if (!is_swap_pte(pte))
        goto unlock;

    entry = pte_to_swp_entry(pte);

    if (!is_migration_entry(entry) ||
        migration_entry_to_page(entry) != old)
        goto unlock;

    get_page(new);
    pte = pte_mkold(mk_pte(new, vma->vm_page_prot));
    if (pte_swp_soft_dirty(*ptep))
        pte = pte_mksoft_dirty(pte);

    /* Recheck VMA as permissions can change since migration started  */
    if (is_write_migration_entry(entry))
        pte = maybe_mkwrite(pte, vma);

#ifdef CONFIG_HUGETLB_PAGE
    if (PageHuge(new)) {
        pte = pte_mkhuge(pte);
        pte = arch_make_huge_pte(pte, vma, new, 0);
    }
#endif
    flush_dcache_page(new);
    set_pte_at(mm, addr, ptep, pte);  // 【把映射的pte页表项内容设置到新页面pte中，重新建立映射关系。】

    if (PageHuge(new)) {
        if (PageAnon(new))
            hugepage_add_anon_rmap(new, vma, addr);
        else
            page_dup_rmap(new);
    } else if (PageAnon(new))
        page_add_anon_rmap(new, vma, addr);
    else
        page_add_file_rmap(new); // 【把新页面newpage添加到RMAP反向映射系统中。】

    /* No need to invalidate - it was non-present before */
    update_mmu_cache(vma, addr, ptep); // 【更新相应的cache】
unlock:
    pte_unmap_unlock(ptep, ptl);
out:
    return SWAP_AGAIN;
}
```
