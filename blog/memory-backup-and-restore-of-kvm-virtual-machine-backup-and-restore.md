> @Date    : 2020-12-14 14:50:30
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# KVM 虚拟机备份和还原之内存备份和还原

> 原文：https://blog.csdn.net/csfreebird/article/details/8160945 2012-11-08 10:32:18 [csfreebird](https://csfreebird.blog.csdn.net/)

有了创建 vm 的自动化脚本，有了删除 vm 的自动化脚本，生活已经简单很多。

但是在某个测试场景中，我们经常需要不断的将 vm 还原到某个起点，然后重新开始测试。每次都删除 / 创建 vm 仍然很慢。

这个时候，可以使用 save/restore 方法。

save/restore 方法只备份和还原当前系统的内存状态，并不会备份磁盘文件。 因此耗时极短，但是使用场合有限，特别注意。

```Bash
virsh save --bypass-cache vm2 /opt/vm2_save --running
```

上面这个命令将 vm2 的当前状态保存到 `/opt/vm2_save` 文件中，这个文件我看了一下，597M。

`--running` 参数表示下次 restore 回来的时候能够自动启动 vm2，这个命令会导致 vm2 被关闭。

在 save 之前可以做一些基础工作，比如 ssh 认证的无密码访问先设定好，apt-cache 的代理设置好，系统升级到最新版本。安装 emacs 等。下次还原回来的时候，这些都有了。

现在还原：

```Bash
virsh destroy vm2
virsh restore /opt/vm2_save --bypass-cache --running
```

必须先关闭虚拟机。
