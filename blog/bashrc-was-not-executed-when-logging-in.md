> @Date    : 2020-10-0‎7‎ 16:38:44
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 打开新终端时没有执行 `.bashrc`

> 原文：https://ubuntuqa.com/article/1516.html 2018-11-15 01:22

## 问题描述

当我在 Ubuntu 12.04 中打开一个新的终端窗口时，`.bashrc` 中的代码不会执行。我在创建 `.bash_aliases` 文件时注意到了这一点。当我打开一个新终端时，别名没有出现。但是，当我键入 `source .bashrc` 时，别名确实显示出来。

每次打开一个新的终端窗口时都应该运行. bashrc 吗？

我该如何做到这一点？

## 最佳解决方法

它不一定是运行；在标准 `.bashrc` 的顶部是这个评论：

```Bash
# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples
```

我相信有一个选项可以将 bash 终端作为登录 shell 运行。使用 Ubuntu，gnome-terminal 通常不作为登录 shell 运行，因此 `.bashrc` 应该直接运行

对于登录 shell(如虚拟终端)，通常运行文件 `~/.profile`，除非您有 `~/.bash_profile`或`~/.bash_login`，但默认情况下不存在。默认情况下，Ubuntu 仅使用 `.profile`

标准 `~/.profile` 有这个：

```Bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
        . "$HOME/.bashrc"
    fi
fi
```

如果可用，则运行 `.bashrc` – 假设您的环境中存在 BASH_VERSION 环境变量。您可以通过输入命令 `echo $BASH_VERSION` 来检查这一点，它应该显示有关版本号的一些信息 – 它不应该是空白的。

## 次佳解决方法

就我而言，`.bash_profile` 中只缺少 `.bashrc` 装载线

```
# include .bashrc if it exists
if [ -f "$HOME/.bashrc" ]; then
    . "$HOME/.bashrc"
fi
```

我手动添加它，它与我的新登录一起工作

## 第三种解决方法

如果未设置 `$BASH_VERSION`，请尝试使用 `chsh` 命令将 shell 设置为 `/bin/bash`

我有一个与 12.04 LTS 类似的问题，结果发现新用户帐户的默认 shell 设置为 `/bin/sh`，这是导致问题的原因

## 第四种方法

`.bash_profile` 保存 bash shell 的配置。当您打开终端时，它首先从 `~/.bash_profile` 读取并执行命令。因此，您可以在 `.bash_profile` 中添加以下内容，以根据 bashrc 设置 shell。

```Bash
. ~/.bashrc
```

## 参考资料

- [.bashrc not executed when opening new terminal](https://askubuntu.com/questions/161249/bashrc-not-executed-when-opening-new-terminal)