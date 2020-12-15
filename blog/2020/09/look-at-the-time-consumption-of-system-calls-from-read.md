> @Date    : 2020-09-14 09:23:36
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 从 read 看系统调用的耗时

> 原文：https://kouucocu.lofter.com/post/1cdb8c4b_50f633f 作者：[kouu](https://kouucocu.lofter.com/) 2009-06-22

## Table of Contents

- [1、fread 和 read 有何不同？](#1、fread-和-read-有何不同？)
- [2、是什么引起的差异？](#2、是什么引起的差异？)
- [3、进一步提高效率？](#3、进一步提高效率？)
- [4、为什么？](#4、为什么？)

## 1、fread 和 read 有何不同？

先看两段代码：

```C
// fread.c
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* pf = fopen("test.file", "r");
	char buf[2] = {0};
	int ret = 0;
	do {
		ret = fread(buf, 1, 1, pf);
	} while (ret);
	return 0;
}
```

```C
// read.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd = open("test.file", 0);
	char buf[2] = {0};
	int ret = 0;
	do {
		ret = read(fd, buf, 1);
	} while (ret);
	return 0;
}
```


两个文件的功能完全一样，打开同一个名为 test.file 的文件，并逐字节地读取整个文件。

【由于没有给出 test.file 所以我自己使用 dd 命令生成一个 100M 的文件】

```bash
taseikyo@node:~/Desktop/200914-test$ dd if=/dev/zero of=test.file bs=1M count=100 
100+0 records in
100+0 records out
104857600 bytes (105 MB, 100 MiB) copied, 0.109864 s, 954 MB/s
taseikyo@node:~/Desktop/200914-test$ ll
total 101M
-rwxrwxr-x 1 taseikyo taseikyo 8.3K 9月  14 09:26 fread
-rw-rw-r-- 1 taseikyo taseikyo  200 9月  14 09:23 fread.c
-rwxrwxr-x 1 taseikyo taseikyo 8.3K 9月  14 09:26 read
-rw-rw-r-- 1 taseikyo taseikyo  215 9月  14 09:24 read.c
-rw-rw-r-- 1 taseikyo taseikyo 100M 9月  14 09:32 test.file
```

将它们编译后得到的可执行程序 fread 和 read 分别在同一台 PC（linux 系统）上执行，得到的如果如下：

```C
taseikyo@node:~/Desktop/200914-test$ time ./fread
real	0m1.804s
user	0m1.796s
sys	0m0.008s
taseikyo@node:~/Desktop/200914-test$ time ./read
real	0m22.908s
user	0m2.084s
sys	0m20.824s
```

发现没有？fread 与 read 的耗时相差数十倍之多！可见啊~ read 一个字节这种写法是相当不可取的！

## 2、是什么引起的差异？

但是，事情为什么会是这样的呢？让我们用 strace 来看看：

```bash
taseikyo@node:~/Desktop/200914-test$ strace ./fread
execve("./fread", ["./fread"], 0xXXXXXXXXXX /* 37 vars */) = 0
...
...
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 4096) = 4096

taseikyo@node:~/Desktop/200914-test$ strace ./read
execve("./read", ["./read"], 0xXXXXXXXXXX /* 37 vars */) = 0
...
...
read(3, "\0", 1)                        = 1
```

看到了吧~ fread 库函数在内部做了缓存，每次读取 4096 个字节；而 read 就老老实实一个字节一个字节地读...

那么再想想，我们读的是什么？是磁盘。难道上面提到的差异，就是因为这 4096 倍的读磁盘次数差而引起的吗？并不是这样。

磁盘是块设备，每次读取的最小单位是块。而当我们通过系统调用读一个字节时，linux 会怎么做呢？它会是读取一个块、然后返回一个字节、再把其余字节都丢掉吗？当然不会，这样的操作系统也太拙劣了...

实际上 linux 的文件系统层（fs 层）不仅会将每次读的一整块数据缓存下来，还有预读机制（一次预读多个块，以减少磁盘寻道时间），并且缓存的内容是放在文件对应的 inode 里面，是可以在进程间共享的。（省略细节若干...）

那么，fread 与 read 执行的耗时差别来自于哪里呢？从代码看，它们都做了相同次数的函数调用；从内核看，它们都造成了基本上相同的磁盘 IO...但是注意到，第一段代码中一共进行了 N（N = 约 24M）次 fread 函数调用，产生约 N/4096 次系统调用；第二段代码中一共进行了 N 次 read 函数调用，产生 N 次系统调用。实际上这里的耗时差就来自于 4096 倍的系统调用次数差！fread() 库函数中缓存的作用并不是减少读磁盘的次数，而是减少系统调用的次数。

由此可见，系统调用比起普通函数调用有很大的开销，编写代码时应当注意避免滥用系统调用。

## 3、进一步提高效率？

为了进一步减少系统调用的次数，关于读文件的这个问题，我们还可以这样做：

```C
// mmap.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
	int fd = open("test.file", 0);
	struct stat statbuf;
	char *start;
	char buf[2] = {0};
	int ret = 0;
	fstat(fd, &statbuf);
	start = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE,
	             fd, 0);
	do {
		*buf = start[ret++];
	} while (ret < statbuf.st_size);
}
```

同样是遍历整个文件，但是读文件的过程中不需要使用系统调用，直接把文件当成内存 buffer 来读就行了。其原理是：mmap 的执行，仅仅是在内核中建立了文件与虚拟内存空间的映射关系。用户访问这些虚拟内存空间时，页表里面并没有这些空间的表项，于是 CPU 产生缺页异常。内核捕捉这些异常，逐渐将文件读入内存，并建立相关的页表项。（省略细节若干...）

将其编译后得到的可执行程序 mmap 和之前的 fread、read 分别在同一台 PC 上执行，得到的如果如下：

```bash
taseikyo@node:~/Desktop/200914-test$ time ./read
real	0m22.192s
user	0m1.960s
sys	0m20.232s
taseikyo@node:~/Desktop/200914-test$ time ./fread
real	0m1.803s
user	0m1.772s
sys	0m0.028s
taseikyo@node:~/Desktop/200914-test$ time ./mmap
real	0m0.370s
user	0m0.368s
sys	0m0.000s
```

mmap 方式与 fread 方式相比，耗时又减少了好几倍。

## 4、为什么？

看到这里，我们不禁要问，系统调用为什么就这么耗时呢？系统调用与普通函数调用到底有什么不同？

1. 两者都是在调用处进行跳转，转到被调用的代码中去执行；

	系统调用使用的 "跳转" 指令相对复杂。因为跳转到内核空间去执行时，CPU 特权级别需要改变（否则没有权限访问到内核空间）。于是，CPU 必须封装一条指令，既实现跳转、又实现特权级别的改变，并且还要保证跳转到的地方就是内核代码（否则用户程序用这个指令假跳一下，自己就拥有特权了）。而软中断指令恰好能满足这三点要求，所以，X86 下实现系统调用的经典方法就是 "INT 0x80"（现在好像换 sysenter 了吧~ 但是指令要做的事情应该不会变）；

2. 两者都是执行到返回点，然后跳转回到原先的调用点；

	系统调用的返回过程还伴随着很多的工作，比如检查是否需要调度、是否有异步信号需要处理等等。然后，既然来的时候改变了 CPU 特权级别，返回的时候还得改回去；

3. 两种调用中，调用前后的代码都在相同的虚拟地址空间中（内核空间也属于用户进程所能看到的虚拟地址空间范围内，尽管进程一般情况下没有权限去访问），地址空间并没有切换；

	运行内核代码时使用的栈是内核栈，系统调用时需要进行栈的切换；

4. 两者的参数传递看似相同；

	普通函数调用是通过栈来传递参数的；而系统调用是通过寄存器来传递参数，寄存器不够用时才逼不得已使用栈。因为栈要切换，参数传递起来不那么简单；（但是在这一点上，系统调用与普通函数调用的耗时并无太大差异。）

5. CPU 执行内核代码和执行用户程序代码没什么区别；

	但是注意到，内核代码对用户参数是充分的不信任。以 read/fread 的 buffer 参数为例，fread 库函数一般不会检查 buffer 参数是否合法。就算想要检查，也没这个能力。他不知道 buffer 是不是个野指针，不知道 buffer 的大小是否与 len 不符，不知道 buffer 指向的这块内存是否可写...他唯一能做的检查只是 buffer 是否为 NULL，可惜这没什么意义。但是通过系统调用进入内核以后，情况就不同了。前面说到的那些检查，统统都要做，并且每次调用都要不厌其烦地做；

以上几点区别，仅是我目前能够想到的。但是管中窥豹，可见一斑。进入内核以后，要做的事情的确是很多很多。