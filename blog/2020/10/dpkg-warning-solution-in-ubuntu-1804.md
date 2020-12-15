> @Date    : 2020-10-05 11:48:13
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

在 node10 上遇到这个问题，而且 warning 多达 180。。。就离谱，不知道谁搞出来的，真的牛皮，搞得我现在 `gcc/g++` 不能用。

# Ubuntu 18.04 中的 dpkg 警告解决方案

> 原文：https://www.pythonf.cn/read/105362 作者：Python Free 时间：2020-05-09

最近在命令行安装软件时，经常弹出来 dpkg 警告，积少成多，终于变成了 3000 多行，试了网上说的给 info 文件夹备份改名的方法，并无卵用，只能上 Google 看看，果然瞎猫碰上了死耗子，通过下面几个步骤解决了问题。

首先在同一目录下，新建三个文件，分别是 txt，fixit.py，fix.sh

【实际上只需要 txt 和 py 就行，后面的 sh 是由py 生成的】

## 复制所有警告

```
dpkg: 警告: 无法找到软件包 wine-stable-amd64 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 linuxqq 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 unixodbc-dev 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libk4a1.1 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libodbc1:amd64 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libjpeg62-turbo:amd64 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libjpeg62-turbo:i386 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 wine-stable 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 odbcinst 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libk4a1.1-dev 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 wine-stable-i386:i386 
...
```

## 写 Python 脚本

【下面是我修改过发 fixit.py，我手动去掉了软件后面的 `:amd64` 后缀】

```Python
import re


def main():
    pat = re.compile("dpkg: 警告: 无法找到软件包 (.+) ")
    miss_pkgs = []
    for line in open("dpkg_warning.txt", encoding="utf-8"):
        pkg = re.match(pat, line)
        if pkg:
            miss_pkgs.append(pkg.group(1).split(":")[0])
    with open("fix.sh", "w") as f:
        f.write("#!/bin/bash\n\n")
        for mpkp in miss_pkgs:
            f.write(f"sudo apt-get -y install --reinstall {mpkp}\n")


if __name__ == "__main__":
    main()
```

## 执行 Shell 脚本

运行完 Python 之后，Shell 脚本就自动生成了，执行即可

```Bash
sudo apt-get -y install --reinstall wine-stable-amd64
sudo apt-get -y install --reinstall linuxqq
sudo apt-get -y install --reinstall unixodbc-dev
...
```

```Bash
>> python fixit.py
```

【可以看到在执行过程中，warning 的确在慢慢减少，说明这个方法有效果！】

【执行完的效果如下】

```
升级了 0 个软件包，新安装了 0 个软件包，重新安装了 1 个软件包，要卸载 0 个软件包，有 91 个软件包未被升级。
需要下载 0 B/3,169 kB 的归档。
解压缩后会消耗 0 B 的额外空间。
dpkg: 警告: 无法找到软件包 libx32gcc-s1 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
dpkg: 警告: 无法找到软件包 libnppial9.1:amd64 的文件名列表文件，现假定该软件包目前没有任何文件被安装在系统里。
(正在读取数据库 ... 系统当前共安装有 267084 个文件和目录。)
正准备解包 .../libnppial9.1_9.1.85-3ubuntu1_amd64.deb  ...
正在将 libnppial9.1:amd64 (9.1.85-3ubuntu1) 解包到 (9.1.85-3ubuntu1) 上 ...
正在设置 libnppial9.1:amd64 (9.1.85-3ubuntu1) ...
正在处理用于 libc-bin (2.27-3ubuntu1.2) 的触发器 ...
```

## 参考

- https://fitzeng.org/2017/11/04/linuxDpkgBug/