> @Date    : 2020-09-14 10:01:11
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Linux 下快速创建大文件命令

> 原文：https://www.jianshu.com/p/5a2b2a0b6468 作者：[倔强的潇洒小姐
](https://www.jianshu.com/u/cebffa585c1b) 2017.08.04 00:41:48

## Table of Contents

- [1、dd 命令](#1、dd-命令)
- [2、truncate 命令](#2、truncate-命令)
- [3、fallocate 命令](#3、fallocate-命令)

## 1、dd 命令

生成一个 1000M 的 test 文件，文件内容为全 0（因从 / dev/zero 中读取，/dev/zero 为 0 源）。但是这样为实际写入硬盘，文件产生速度取决于硬盘读写速度，如果想要产生超大文件，速度很慢。

```bash
[root@node www]# dd if=/dev/zero of=test1 bs=1M count=1000
 1000+0 records in
 1000+0 records out
 1048576000 bytes (1.0 GB) copied, 16.6081 s, 63.1 MB/s       //内存操作速度
```

在某种场景下，我们只想让文件系统认为存在一个超大文件在此，但是并不实际写入硬盘。则可以使用 **seek**

1. count=0 表示读写 0 次，指定生成文件的大小为 0M

```bash
[root@node www]# dd if=/dev/zero of=test2 bs=1M count=0 seek=100000
  0+0 records in
  0+0 records out
  0 bytes (0 B) copied, 0.000221494 s, 0.0 kB/s
```

2. count=50 表示读写 50 次，指定生成文件的大小为 50M

```bash
[root@node www]# dd if=/dev/zero of=test3 bs=1M count=50 seek=100000
  50+0 records in
  50+0 records out
  52428800 bytes (52 MB) copied, 0.066445 s, 789 MB/s
 [root@node www]# ls -l test3              //查看目录大小
 -rw-r--r-- 1 root root 104910028800 Aug  3 23:50 test3
```

此时创建的文件在文件系统中的显示大小为 100000MB，但是并不实际占用 block，因此创建速度与内存速度相当。

- if （input file）代表输入文件 / 目录，如果不指定 if，默认就会从 stdin 中读取输入
- of （output file）代表输出文件 / 目录，如果不指定 of，默认就会将 stdout 作为默认输出
- bs 代表每次读入的 block 大小
- count：读取的 block 个数  
- bs * count = 文件大小
- /dev/zero 是 Linux 提供的一个特殊的字符设备，它的特点是可以永远读该文件，每次读取的结果都是二进制 0
- seek：跳过输出文件中指定大小的部分，并不实际写入

## 2、truncate 命令

- 将文件缩减或扩展至指定大小。
- 选项 -s，即 size（大小）
	1. 指定文件不存在则创建
	2. 指定文件超出指定大小则超出的数据将丢失
	3. 指定文件小于指定大小则用 0 补足。

```bash
[root@node www]# truncate -s 10G test4
 [root@node www]# ls -l test4
 -rw-r--r-- 1 root root 10737418240 Aug  3 23:14 test4
```

注意点：

- 这种文件被称为 “空洞文件”，文件的部分内容并没有实际存在于硬盘上
- du（disk use）：默认显示的是真正的磁盘占用

```bash
[root@node www]# truncate -s 1G 123.jpg    ///文件不存在时自动创建
 [root@node www]# ls -l 123.jpg
 -rw-r--r-- 1 root root 1073741824 Aug  4 00:12 123.jpg
 [root@node www]# du 123.jpg
 0  123.jpg
 [root@node www]# truncate -s 500M 123.jpg      //修改文件大小
 [root@node www]# ls -l 123.jpg
 -rw-r--r-- 1 root root 524288000 Aug  4 00:13 123.jpg
 [root@node www]# du 123.jpg
 0  123.jpg
```

## 3、fallocate 命令

```bash
[root@node www]# fallocate -l 10G test4
 fallocate: test4: fallocate failed: Operation not supported    //目录创建失败，只生成了空目录
 [root@node www]# ls -l test4
 -rw-r--r-- 1 root root 0 Aug  4 00:29 test4
 [root@node www]# du test4
 0  test4
```

- fallocate 命令可以为文件预分配物理空间
- -l 后接空间大小，默认单位为字节。也可后跟 k、m、g、t、p、e 来指定单位，分别代表 KB、MB、GB、TB、PB、EB