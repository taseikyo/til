> @Date    : 2020-11-05 11:02:33
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# LINUX 下防止文件被误删除或修改

> 原文：http://smilejay.com/2020/06/linux-prevent-files-from-accidental-deletion/ 06/21/2020

## Table of Contents

- [chattr 的用法如下](#chattr-的用法如下)
- [实例操作](#实例操作)

有时我们的一些重要的文件或目录，不希望被误删除或者修改，我们可以对其加上特殊的属性使其不可修改。。  
如果遇到 root 权限下，删除文件也也被提示无权限 “Operation not permitted”，那么你可以查看一下文件是否被设置为不可修改的属性。

`chattr`（Change Attribute 的缩写）命令就是 Linux 改变文件属性的命令。  
对应地，`lsattr` 命令可以列出文件的属性。

### chattr 的用法如下

```Bash
chattr - change file attributes on a Linux file system

用法概要：

chattr [ -RVf ] [ -v version ] [ -p project ] [ mode ] files...

最常用的参数包括：

-R 对一个目录及其子目录的属性修改

操作符 +，追加指定属性到文件已存在属性中

操作符 -，删除指定属性

关键属性，我一般最常用的就是 i（不可修改）， A file with the 'i' attribute cannot be modified。
```

对于 lsattr 就是更简单一些了，只是列出文件的属性。

### 实例操作

```Bash
[jay@my-host:/tmp]$ touch a.txt

[jay@my-host:/tmp]$ sudo chattr +i a.txt

[jay@my-host:/tmp]$ lsattr a.txt

----i---------e---- a.txt

# 这里有一个 i 属性

[jay@my-host:/tmp]$ rm -f a.txt

rm: cannot remove ‘a.txt’: Operation not permitted

# 删除文件失败了

[jay@my-host:/tmp]$ sudo rm -f a.txt

rm: cannot remove ‘a.txt’: Operation not permitted

# root 账号也删除文件失败了

[jay@my-host:/tmp]$ sudo chattr -i a.txt

[jay@my-host:/tmp]$ lsattr a.txt

--------------e---- a.txt

# 属性 i 应去掉了

[jay@my-host:/tmp]$ rm -f a.txt
```

### 完整属性

chattr 提供不同的属性，也就是 aAcCdDeijsStTu。每个字符代表一个特定文件属性。

```Bash
a – 只能向文件中添加数据
A – 不更新文件或目录的最后访问时间
c – 将文件或目录压缩后存放
C – 不适用写入时复制机制（CoW）
d – 设定文件不能成为 dump 程序的备份目标
D – 同步目录更新
e – extend 格式存储
i – 文件或目录不可改变
j – 设定此参数使得当通过 mount 参数：data=ordered 或者 data=writeback 挂载的文件系统，文件在写入时会先被记录在日志中
P – project 层次结构
s – 安全删除文件或目录
S – 即时更新文件或目录
t – 不进行尾部合并
T – 顶层目录层次结构
u – 不可删除
```
