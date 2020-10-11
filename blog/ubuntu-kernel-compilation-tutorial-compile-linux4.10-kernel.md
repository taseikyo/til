> @Date    : 2020-10-11 20:47:53
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# ubuntu 内核编译教程－编译 linux 4.10 内核

> 原文：https://www.jianshu.com/p/5e37d91bfbbe 作者：[DecadeHeart](https://www.jianshu.com/u/daa5c20df567) 2017.03.03 13:59:18

## 1 环境准备

1. 准备 linux 源码和补丁

可在 [官网](http://www.kernel.org) 下载镜像，选择阿里的镜像更为迅速

```Bash
wget http://mirrors.aliyun.com/linux-kernel/v4.x/linux-4.5.tar.xz
wget http://mirrors.aliyun.com/linux-kernel/v4.x/patch-4.5.xz
```

2. 准备安装环境

首先执行 apt update 来更新软件源，然后安装需要的环境

```Bash
apt install kernel-package build-essential libncurses5-dev fakeroot
```

3. 解压缩内核

```Bash
xz -d linux-4.10.tar.xz
tar –xvf linux-4.10.tar
```

-[4958474-3e3b1ed75fddba42.webp]

解压后得到 linux.4.10，然后将内核目录 linux-4.10 复制到 /usr/src，然后进入 /usr/src

```Bash
sudo cp -r linux-4.10 /usr/src
cd /usr/src
```

## 2 准备编译

1. 编译配置

看以前的内核版本号，将里面的 `.config` 文件复制到 linux-4.10 文件夹中：

通过 ls 可以发现。我的内核文件夹是 linux-headers-4.8-39-generic，我们应当将这个文件夹中的 `.config` 文件复制到 4.10 文件夹中

```Bash
cp linux-headers-4.8.0-39-generic/.config linux-4.10/
cd linux-4.10
```

然后执行 make menuconfig 打开可视化菜单

选择 load→OK→Save→OK→EXIT→EXIT

-[4958474-fa495e4133ee8f6c.webp]

## 3 编译内核

1. 编译启动映像

```Bash
make bzImage -jN
```

-[4958474-544e0b7bc6929718.webp]

这里的 N 是你的 CPU 核数 x2，比如我是双核，则执行 j4 
如果嫌麻烦也可以直接运行 make bzImage

这里可能会出现两个错误：

fatal error: openssl/opensslv.h: No such file or directory

这是因为没有安装 openssl 的，需要先安装 openssl： apt-get install libssl-dev

bc: not found。需要安装 bc：apt-get install bc

安装对应依赖后再运行

2. 编译模块

```Bash
make modules - jN
```

-[4958474-83687977675a426c.webp]

## 4 安装内核

先安装模块

```Bash
make modules_install
```

-[4958474-74f94a20f9c5c52d.webp]

再安装内核

```Bash
make install
```

-[4958474-1119a9f6a4a48e35.webp]

## 5 更改启动 grub

grub 就是系统启动的一个程序，若要运行编译好的内核，则需要修改相对应的 grub

```Bash
mkiniramfs 4.10.0 -o /boot/inird.img-4.10
update-grub2
```

该命令会帮助我们自动修改 grub

修改之后，可以查看内核版本

> uname -a