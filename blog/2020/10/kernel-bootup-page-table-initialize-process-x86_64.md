> @Date    : 2020-10-11 21:51:45
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo


# 内核启动页表初始化过程（X86_64）

KERNEL BOOTUP PAGE TABLE INITIALIZE PROCESS（X86_64）

> 原文：https://void-shana.moe/linux/kernel-bootup-page-table-initialize-processx86_64.html  November 23, 2017 作者：[VOID001](https://void-shana.moe/author/void001)

This article will provide detailed information about the kernel bootup page table setup.

In a brief view, the kernel setup page table in three steps:

1. Setup the 4GB identity mapping
2. Setup 64bit mode page table early_top_pgt
3. Setup 64bit mode page table init_top_pgt

The last two steps are both higher mapping: Map the 512MB physical address to virtual address 0xffff80000000 – 0xffff80000000 + 512MB.

Next, we will talk about the details. We will use the 4.14 version code to explain the process.

*You need to know the IA32e paging mechanism and relocation to read the article. The Intel manual has a good explaination of IA32e paging*

https://github.com/torvalds/linux/blob/v4.14/arch/x86/boot/compressed/head_64.S

## Before decompression

When the kernel is being loaded, it is either decompressed by a third-party bootloader like GRUB2 or by the kernel itself. Now we will talk about the second condition. The code started from arch/x86/boot/header.S . It is in 16bit real mode at the time. Then in code arch/x86/boot/compressed/head_64.S  We setup the first page table in 32bit mode. We need this page table to take us to do take us to 64bit mode.

The following code is the set-up process

```asm
/*
 * Prepare for entering 64 bit mode
 */

	/* Load new GDT with the 64bit segments using 32bit descriptor */
	addl	%ebp, gdt+2(%ebp)
	lgdt	gdt(%ebp)

	/* Enable PAE mode */
	movl	%cr4, %eax
	orl	$X86_CR4_PAE, %eax
	movl	%eax, %cr4

 /*
  * Build early 4G boot pagetable
  */
	/*
	 * If SEV is active then set the encryption mask in the page tables.
	 * This will insure that when the kernel is copied and decompressed
	 * it will be done so encrypted.
	 */
	call	get_sev_encryption_bit
	xorl	%edx, %edx
	testl	%eax, %eax
	jz	1f
	subl	$32, %eax	/* Encryption bit is always above bit 31 */
	bts	%eax, %edx	/* Set encryption mask for page tables */
1:

	/* Initialize Page tables to 0 */
	leal	pgtable(%ebx), %edi
	xorl	%eax, %eax
	movl	$(BOOT_INIT_PGT_SIZE/4), %ecx
	rep	stosl

	/* Build Level 4 */
	leal	pgtable + 0(%ebx), %edi
	leal	0x1007 (%edi), %eax
	movl	%eax, 0(%edi)
	addl	%edx, 4(%edi)

	/* Build Level 3 */
	leal	pgtable + 0x1000(%ebx), %edi
	leal	0x1007(%edi), %eax
	movl	$4, %ecx
1:	movl	%eax, 0x00(%edi)
	addl	%edx, 0x04(%edi)
	addl	$0x00001000, %eax
	addl	$8, %edi
	decl	%ecx
	jnz	1b

	/* Build Level 2 */
	leal	pgtable + 0x2000(%ebx), %edi
	movl	$0x00000183, %eax
	movl	$2048, %ecx
1:	movl	%eax, 0(%edi)
	addl	%edx, 4(%edi)
	addl	$0x00200000, %eax
	addl	$8, %edi
	decl	%ecx
	jnz	1b

	/* Enable the boot page tables */
	leal	pgtable(%ebx), %eax
	movl	%eax, %cr3
```

Notice that from the comment above. %ebx contain the address where we move kernel to make a safe decompression. Which means we should treat %ebx as an offset to the compiled binary. The compiled binary start at 0. So we fix-up the difference to reach the real physical address.

```asm
/* Build Level 4 */
leal	pgtable + 0(%ebx), %edi
leal	0x1007 (%edi), %eax
movl	%eax, 0(%edi)
addl	%edx, 4(%edi)
```

The above code setup Top level page directory. This only set the lowest page directory entry to (1007 + pgtable). This is a pointer to the next level page table. And next level page table start at 0x1000 + pgtable. The last line adds %edx to 4+%edi will set encryption masks if SEV is active. Currently, we can omit this line.

Then we look at the next level.

```asm
	/* Build Level 3 */
	leal	pgtable + 0x1000(%ebx), %edi
	leal	0x1007(%edi), %eax
	movl	$4, %ecx
1:	movl	%eax, 0x00(%edi)
	addl	%edx, 0x04(%edi)
	addl	$0x00001000, %eax
	addl	$8, %edi
	decl	%ecx
	jnz	1b

```

Here, we can see we set up four entries. and each entry point to another page directory.

```
	/* Build Level 2 */
	leal	pgtable + 0x2000(%ebx), %edi
	movl	$0x00000183, %eax
	movl	$2048, %ecx
1:	movl	%eax, 0(%edi)
	addl	%edx, 4(%edi)
	addl	$0x00200000, %eax
	addl	$8, %edi
	decl	%ecx
	jnz	1b

```

This is the last level of page directory, these entry will point to a physical page frame directly. Now let’s take a look at the code. It sets up 2048 entries. Each entry with a Page Flag R/W = 1 U/S = 0 PS = 1. This means the page is read / write by kernel only and its size is 2MB. Each PTE(Page Table Entry) is a 8 Byte block data. So one page can contain at most 512 entries. Here kernel setup 4 pages of Level 2 Page Directory. The following image show the current page table structure.

In total we have 2048 * 2MB = 4GB physical address, identity mapped to 0 – 4GB linear address.

![](https://void-shana.moe/wp-content/uploads/2017/11/aaa-e1511368338472-1024x768.jpg)

Then we use a long return to switch to 64bit mode.

![](https://void-shana.moe/wp-content/uploads/2017/11/Screenshot_20171123_003421-1024x503.png)

Kernel push the startup_64 and CS register to stack, then perform a long return to enter 64bit mode.  And then after copy the compressed kernel, we jump to symbol relocated

```
/*
 * Jump to the relocated address.
 */
	leaq	relocated(%rbx), %rax
	jmp	*%rax

```

In the relocated code, we do the kernel decompression.

```
/*
 * Do the extraction, and jump to the new kernel..
 */
	pushq	%rsi			/* Save the real mode argument */
	movq	%rsi, %rdi		/* real mode address */
	leaq	boot_heap(%rip), %rsi	/* malloc area for uncompression */
	leaq	input_data(%rip), %rdx  /* input_data */
	movl	$z_input_len, %ecx	/* input_len */
	movq	%rbp, %r8		/* output target address */
	movq	$z_output_len, %r9	/* decompressed length, end of relocs */
	call	extract_kernel		/* returns kernel location in %rax */
	popq	%rsi

```

The decompressed kernel is compiled at high address(we take ffffffff81000000 for example). But now we don’t have the correct page table to do the mapping. Fortunately, the **extract_kernel** function returns the physical address of the decompressed kernel. (Which is %ebp, equals to %ebx). After decompression, %rax contains the kernel physical start address. We jump there to perform the further setup.

## Start execution in vmlinux

We now arrived at arch/x86/kernel/head_64.S. Before we continue, we must notice two things first.

* After decompression, the kernel is placed at physical address %rbp (If we do not set CONFIG_RELOCATABLE it’s equal to 0x1000000  
    ).
* After decompression, we now in the kernel code compiled with the virtual address ffffffff81000000(as we mentioned above).

So here is a big pitfall. We cannot access ANY of the symbols in vmlinux currently. Because we only have a basic identity mapping now. But we need to visit the variables. How can we make it? The kernel uses a trick here, I will show it below

```
static void __head *fixup_pointer(void *ptr, unsigned long physaddr)
{
	return ptr - (void *)_text + (void *)physaddr;
}


```

This function fixup the symbol virtual address to the real physical address.

**“Current Valid Addr” = “Virtual Hi Addr” – “Kernel Virtual Address Base Addr” + “%rax Extracted kernel physical address”.**

Now we continue reading the arch/x86/kernel/head_64.S  assembly code, this is where we landed from arch/x86/compressed/head_64.S

The enrty is startup_64:

```
startup_64:
	/*
	 * At this point the CPU runs in 64bit mode CS.L = 1 CS.D = 0,
	 * and someone has loaded an identity mapped page table
	 * for us.  These identity mapped page tables map all of the
	 * kernel pages and possibly all of memory.
	 *
	 * %rsi holds a physical pointer to real_mode_data.
	 *
	 * We come here either directly from a 64bit bootloader, or from
	 * arch/x86/boot/compressed/head_64.S.
	 *
	 * We only come here initially at boot nothing else comes here.
	 *
	 * Since we may be loaded at an address different from what we were
	 * compiled to run at we first fixup the physical addresses in our page
	 * tables and then reload them.
	 */

	/* Set up the stack for verify_cpu(), similar to initial_stack below */
	leaq	(__end_init_task - SIZEOF_PTREGS)(%rip), %rsp

	/* Sanitize CPU configuration */
	call verify_cpu

	/*
	 * Perform pagetable fixups. Additionally, if SME is active, encrypt
	 * the kernel and retrieve the modifier (SME encryption mask if SME
	 * is active) to be added to the initial pgdir entry that will be
	 * programmed into CR3.
	 */
	leaq	_text(%rip), %rdi
	pushq	%rsi
	call	__startup_64
	popq	%rsi

	/* Form the CR3 value being sure to include the CR3 modifier */
	addq	$(early_top_pgt - __START_KERNEL_map), %rax
	jmp 1f

```

In this article, we talk about self loading, instead of using a third party 64bit bootloader like GRUB. So as the comment said, we come here from arch/x86/boot/compressed/head_64.S. If we config the kernel with CONFIG_RELOCATABLE, the kernel won’t run at the place we compiled, page table fixup need to be performed. The page table is fixed in **__startup_64**

```
unsigned long __head __startup_64(unsigned long physaddr,
				  struct boot_params *bp)
{
	unsigned long load_delta, *p;
	unsigned long pgtable_flags;
	pgdval_t *pgd;
	p4dval_t *p4d;
	pudval_t *pud;
	pmdval_t *pmd, pmd_entry;
	int i;
	unsigned int *next_pgt_ptr;

	/* Is the address too large? */
	if (physaddr >> MAX_PHYSMEM_BITS)
		for (;;);

	/*
	 * Compute the delta between the address I am compiled to run at
	 * and the address I am actually running at.
	 */
	load_delta = physaddr - (unsigned long)(_text - __START_KERNEL_map);

	/* Is the address not 2M aligned? */
	if (load_delta & ~PMD_PAGE_MASK)
		for (;;);

	/* Activate Secure Memory Encryption (SME) if supported and enabled */
	sme_enable(bp);

	/* Include the SME encryption mask in the fixup value */
	load_delta += sme_get_me_mask();

	/* Fixup the physical addresses in the page table */

	pgd = fixup_pointer(&early_top_pgt, physaddr);
	pgd[pgd_index(__START_KERNEL_map)] += load_delta;

	if (IS_ENABLED(CONFIG_X86_5LEVEL)) {
		p4d = fixup_pointer(&level4_kernel_pgt, physaddr);
		p4d[511] += load_delta;
	}

        /* Omit some fixup code for simplicity */

	return sme_get_me_mask();
}


```

We compute the load_delta, and fixup the early_top_pgt. Now we just assume we don’t configure the kernel with CONFIG_RELOCATABLE. Then we can look at the page table built at compile time. First we look at the top level **early_top_pgt.** It set only the last entry point to level3 page table. which means only virtual address start with 0xff8000000000 will be valid.

```
NEXT_PAGE(early_top_pgt)
	.fill	511,8,0
#ifdef CONFIG_X86_5LEVEL
	.quad	level4_kernel_pgt - __START_KERNEL_map + _PAGE_TABLE_NOENC
#else
	.quad	level3_kernel_pgt - __START_KERNEL_map + _PAGE_TABLE_NOENC
#endif

```

Now we look at the next level (We do not use 5 Level Paging).

```
NEXT_PAGE(level3_kernel_pgt)
	.fill	L3_START_KERNEL,8,0
	/* (2^48-(2*1024*1024*1024)-((2^39)*511))/(2^30) = 510 */
	.quad	level2_kernel_pgt - __START_KERNEL_map + _KERNPG_TABLE_NOENC
	.quad	level2_fixmap_pgt - __START_KERNEL_map + _PAGE_TABLE_NOENC

```

This level we have two entries, one for kernel address space. One for fixmap address space, fixmap address space is used for IO mapping, DMA, etc. Now we just look at the fixmap address space. It’s at index 510. in binary mode 0b111111110. Combine with the top level we get a smaller linear address space. Only address start from 0xffff80000000 is valid.

Then it’s the last level page directory. **level2_kernel_pgt**

```
NEXT_PAGE(level2_kernel_pgt)
	/*
	 * 512 MB kernel mapping. We spend a full page on this pagetable
	 * anyway.
	 *
	 * The kernel code+data+bss must not be bigger than that.
	 *
	 * (NOTE: at +512MB starts the module area, see MODULES_VADDR.
	 *  If you want to increase this then increase MODULES_VADDR
	 *  too.)
	 */
	PMDS(0, __PAGE_KERNEL_LARGE_EXEC,
		KERNEL_IMAGE_SIZE/PMD_SIZE)

```

This level is a mapping to physical address 0 – 512MB (it maps more than that, but we only need 512MB) So we get the current mapping then.

**Linear: 0xffff80000000 – 0xffff80000000 + 512MB =====> Physical: 0 – 512MB**

You can use a gdb to print the page table and debug it in your own. Here is a simple “it works!” script for parsing the page directory entry

```
#!/usr/bin/python

import argparse

def main():
    parser = argparse.ArgumentParser(description='Page Table Entry Decodern Convert into human-friendly mode')
    parser.add_argument('value', type=str)
    args = parser.parse_args()
    value = (int(args.value, 16))
    P = value & 0x0000000000000001
    if not P:
        print("PE = 0, page not present")
        return
    else:
        print("PE = 1")

    RW = value & 0x0000000000000002
    if not RW:
        print("R/W = 0, Only Read access")
    else:
        print("R/W = 1, Read/Write access")

    US = value & 0x0000000000000004
    if not US:
        print("U/S = 0, only for kernel access")
    else:
        print("U/S = 1, user/kernel access")
    
    PS = (value & 0x0000000000000080) >> 7
    PHY = ((value >> 12) & 0x000ffffffffff) << 12

    print("PS = {:d}".format(PS))
    print("PHYADDR = {:x}".format(PHY))


if __name__ == '__main__':
    main()


```

Kernel load the early_top_pgt into cr3 using the following code

```
    addq	$(early_top_pgt - __START_KERNEL_map), %rax
    ...
    addq	phys_base(%rip), %rax
    movq	%rax, %cr3

```

The current page table structure is shown below:

![](https://void-shana.moe/wp-content/uploads/2017/11/pasted-image-0-e1511372882463.png)

Now we are free to visit any kernel symbol without to force convert the address using **fixup_address** or something else. We can go further to the init/main.c code.

We use a long return to get to get to x86_64_start_kernel

```
	pushq	$.Lafter_lret	# put return address on stack for unwinder
	xorq	%rbp, %rbp	# clear frame pointer
	movq	initial_code(%rip), %rax
	pushq	$__KERNEL_CS	# set correct cs
	pushq	%rax

```

**initial_code** here is defined as **x86_64_start_kernel**.

Moving to init/main.c
---------------------

We are now at arch/x86/kernel/head64.c and in function **x86_64_start_kernel** 

```
asmlinkage __visible void __init x86_64_start_kernel(char * real_mode_data)
{
	/*
	 * Build-time sanity checks on the kernel image and module
	 * area mappings. (these are purely build-time and produce no code)
	 */
	BUILD_BUG_ON(MODULES_VADDR < __START_KERNEL_map);

        /* Omit some initialization code for simplicity */

	/* set init_top_pgt kernel high mapping*/
	init_top_pgt[511] = early_top_pgt[511];

	x86_64_start_reservations(real_mode_data);
}

```

We set up **init_top_pgt[511]** same as **early_top_pgt[511]**  **. init_top_pgt** is the final kernel page table. From **x86_64_start_reservations** we get to **start_kernel** This is a function located at init/main.c

```
asmlinkage __visible void __init start_kernel(void)
{
        /* Omit some code for simplicity */

	boot_cpu_init();
	page_address_init();
	pr_notice("%s", linux_banner);
	setup_arch(&command_line);

        /* Omit some code for simplicity */

	rest_init();
}

```

After calling **setup_arch**, CR3 is loaded with init_top_pgt. Then the kernel page table will not change. I wonder if there is a change to switch kernel page table from 2MB size physical page to 4KB physical page, but it seems that the CR3 remained unchanged, and I examined the page entries, they remain unchanged, too. Even the code has executed into **rest_init** then do_idle

The following function is a simple debug function to output the current CR3 register since GDB cannot get the CR3 register value, I just print it out to see when it changed.

```
asmlinkage __visible unsigned long shana_debug_cr3(void) {
    unsigned long cr3_value = 0xffffffff;
    asm volatile("mov %%cr3, %0"
            : "=r"(cr3_value));
    printk("shana_debug_cr3: %x", cr3_value);
    return cr3_value;
}

```