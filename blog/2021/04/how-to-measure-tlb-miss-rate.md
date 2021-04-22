> @Date    : 2021-04-22 19:18:55
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 【内存】TLB缓存是个神马鬼，如何查看TLB miss？

> 原文：https://www.cnblogs.com/bandaoyu/p/14624842.html 2021-01-29 14:22 [半岛小鱼](https://www.cnblogs.com/bandaoyu/)

## Table of Contents

- [页表带来的问题](#页表带来的问题)
- [TLB 应运而生](#tlb-应运而生)
	- [TLB 原理](#tlb-原理)
- [如何查看 TLB miss](#如何查看-tlb-miss)
- [扩展](#扩展)
- [参考文献](#参考文献)

Linux 在 v2.6.11 以后，最终采用的方案是 4 级页表，分别是：

- PGD：page Global directory(47-39), 页全局目录
- PUD：Page Upper Directory(38-30)，页上级目录
- PMD：page middle directory(29-21)，页中间目录
- PTE：page table entry(20-12)，页表项

这样，一个 64 位的虚拟空间，就需要：2^9 个 PGD + 2^9 个 PUD + 2^9 个 PMD + 2^9 个 PTE = 2048 个页表数据结构。现在的页表数据结构被扩展到了 8 byte。仅仅需要 (2048\*8=)16K 就可以支持起 (2^48 =)256T 的进程地址空间。

## 页表带来的问题

处理器引入 MMU 后，读取指令、数据需要访问两次内存：

首先通过查询**页表**得到物理地址，然后访问该物理地址读取指令、数据。

既由于页表存放在主存中，因此程序每次访存至少需要两次（单级页表）：一次访存获取物理地址，第二次访存才获得数据。

虽然 16K 的页表数据支持起了 256T 的地址空间寻址。**但是，这也带来了额外的问题，页表是存在内存里的。那就是一次内存 IO 光是虚拟地址到物理地址的转换就要去内存查 4 次页表（4 级），再算上真正的内存访问，竟然需要 5 次内存 IO 才能获取一个内存数据!!**

## TLB 应运而生

为了减少因为 MMU 导致的处理器性能下降，引入了 **TLB**，**TLB 是 Translation Lookaside Buffer** 的简称，可翻译为 “地址转换后援缓冲器”，也可简称为 “快表”。

简单地说，TLB 就是页表的 Cache，其中存储了当前最可能被访问到的页表项，其内容是部分页表项的一个副本。只有在 TLB 无法完成地址翻译任务时，才会到内存中查询页表，这样就减少了页表查询导致的处理器性能下降。

### TLB 原理

当 cpu 要访问一个虚拟地址 / 线性地址时，CPU 会首先根据虚拟地址的高 20 位（20 是 x86 特定的，不同架构有不同的值）在 TLB 中查找。如果是表中没有相应的表项，称为 TLB miss，需要通过访问慢速 RAM 中的页表计算出相应的物理地址。同时，物理地址被存放在一个 TLB 表项中，以后对同一线性地址的访问，直接从 TLB 表项中获取物理地址即可，称为 TLB hit。

归纳如下：

1. CPU 产生一个虚拟地址
2. MMU 从 TLB 中获取页表，翻译成物理地址
3. MMU 把物理地址发送给 L1/L2/L3 / 内存
4. L1/L2/L3 / 内存将地址对应数据返回给 CPU

由于第 2 步是类似于寄存器的访问速度，所以如果 TLB 能命中，则虚拟地址到物理地址的时间开销几乎可以忽略。如果想了解 TLB 更详细的工作机制，请参考《深入理解计算机系统 - 第 9 章虚拟内存》

想像一下 x86_32 架构下没有 TLB 的存在时的情况，对线性地址的访问，首先从 PGD 中获取 PTE（第一次内存访问），在 PTE 中获取页框地址（第二次内存访问），最后访问物理地址，总共需要 3 次 RAM 的访问。如果有 TLB 存在，并且 TLB hit，那么只需要一次 RAM 访问即可。

## 如何查看 TLB miss

既然 TLB 缓存命中很重要，那么有什么工具能够查看你的系统里的命中率呢？ 还真有

```Bash
perf stat -e dTLB-loads,dTLB-load-misses,iTLB-loads,iTLB-load-misses -p $PID

Performance counter stats for process id '21047':

627,809 dTLB-loads
8,566 dTLB-load-misses # 1.36% of all dTLB cache hits
2,001,294 iTLB-loads
3,826 iTLB-load-misses # 0.19% of all iTLB cache hits
```

iTLB-loads 可大于也可小于 iTLB-load-misses：https://stackoverflow.com/questions/49933319/how-to-interpret-perf-itlb-loads-itlb-load-misses

On your Broadwell processor, perf maps iTLB-loads to ITLB_MISSES.STLB_HIT, which represents the event of a TLB lookup that misses the L1 ITLB but hits the unified TLB for all page sizes, and iTLB-load-misses to ITLB_MISSES.MISS_CAUSES_A_WALK, which represents the event of a TLB lookup that misses both the L1 ITLB and the unified TLB (causing a page walk) for all page sizes. Therefore, iTLB-load-misses can be larger or smaller than or equal to iTLB-loads. They are independent events.

iTLB 和 dTLB 含义：

- https://zhengheng.me/2015/11/12/perf-stat
- https://blog.csdn.net/u011630575/article/details/66476165

## 扩展

> 因为 TLB 并不是很大，只有 4k，而且现在逻辑核又造成会有两个进程来共享。所以可能会有 cache miss 的情况出现。而且一旦 TLB miss 造成的后果可比物理地址 cache miss 后果要严重一些，最多可能需要进行 5 次内存 IO 才行。建议你先用上面的 perf 工具查看一下你的程序的 TLB 的 miss 情况，如果确实不命中率很高，那么 Linux 允许你使用大内存页，很多大牛包括 PHP7 作者鸟哥也这样建议。这样将会大大减少页表项的数量，所以自然也会降低 TLB cache miss 率。所要承担的代价就是会造成一定程度的内存浪费。在 Linux 里，大内存页默认是不开启的。

## 参考文献

- [Linux 内核 4 级页表的演进](https://blog.csdn.net/HMSIWTV/article/details/39956981)
- [什么是 TLB 和 PCID？为什么要有 PCID？为什么 Linux 现在才开始使用它？](https://zhuanlan.zhihu.com/p/32718446)
- [MMU 内存管理单元](https://www.cnblogs.com/alantu2018/p/9002309.html)
- [perf 统计 内存相关 event](https://blog.csdn.net/mrpre/article/details/83537311)
- https://blog.csdn.net/zhangyanfei01/article/details/100053533
