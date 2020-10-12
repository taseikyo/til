> @Date    : 2020-10-11 21:03:13
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Getting the CR3 value for a PID in Linux

> 原文：https://carteryagemann.com/pid-to-cr3.html 作者：[Carter Yagemann](https://carteryagemann.com/) Mon 30 January 2017

Writing low level code can be difficult due to the lack of examples on the internet. The answer is generally sitting somewhere in a 3,000 page manual where only the most dedicated programmers will find it.

Last week I had such an experience. Currently my research involves a lot of x86 specific programming and virtual machine introspection (VMI). To test one of the proof-of-concept hypervisors I'm working on, I needed a way to quickly convert Linux PID values into the corresponding value that gets loaded into the CR3 register when that process is executing on the CPU. For those who are unfamiliar with the x86 CPU architecture, I recommend reading [this page](https://www.kernel.org/doc/gorman/html/understand/understand006.html) on Linux x86 page table management. The short story is when a process is executed on an x86 CPU, the CR3 register is loaded with the _physical_ address of that process's _page global directory_ (PGD). This is necessary so the CPU can perform translations from virtual memory address to physical memory addresses. Since every process needs its own PGD, the value in the CR3 register will be unique for each scheduled process in the system. This is very convenient for VMI because it means we don't need to constantly scan the guest kernel's memory to keep track of which process is being executed. Instead, we can just monitor writes to the CR3 register.

However, just tracking changes to the CR3 register doesn't give us much insight into what the guest kernel is doing. This is commonly referred to as the _semantic gap_ problem. In order to cross this gap, we need to map the PID values of the processes we're interested in to their corresponding CR3 values. The following Linux kernel module code snippet does just that:

```C
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/io.h>

unsigned long pid_to_cr3(int pid) {
	struct task_struct *task;
	struct mm_struct *mm;
	void *cr3_virt;
	unsigned long cr3_phys;

	task = pid_task(find_vpid(pid), PIDTYPE_PID);

	if (task == NULL)
		return 0; // pid has no task_struct

	mm = task->mm;

	// mm can be NULL in some rare cases (e.g. kthreads)
	// when this happens, we should check active_mm
	if (mm == NULL) {
		mm = task->active_mm;
	}

	if (mm == NULL)
		return 0; // this shouldn't happen, but just in case

	cr3_virt = (void *) mm->pgd;
	cr3_phys = virt_to_phys(cr3_virt);

	return cr3_phys;
}
```

It should be noted that while the CR3 register is useful for tracking which *process* is being executed, it cannot track which *thread* is executing because threads share memory and therefore will have the same PGD and CR3 value. Keeping track of the scheduling of threads via introspection is a more complicated task and is a topic for another time.

For simplicity I implemented the conversion code as a Linux kernel module. If you're interested in how to do this conversion using pure introspection on an unmodified kernel, you should checkout [libVMI's code](https://github.com/libvmi/libvmi/blob/master/libvmi/os/linux/memory.c#L145).