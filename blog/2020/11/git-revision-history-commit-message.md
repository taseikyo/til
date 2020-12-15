> @Date    : 2020-11-19 10:37:53
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# git 修改历史提交（commit）信息

> 原文：https://blog.csdn.net/qq_17011423/article/details/104648075 2020-03-04 10:38:03 [我怀念的:)](https://me.csdn.net/qq_17011423)

## Table of Contents

- [1 修改最近一次 commit 的信息](#1-修改最近一次-commit-的信息)
- [2 修改最近两个或者两次上的 commit 信息](#2-修改最近两个或者两次上的-commit-信息)

我们在开发中使用 git 经常会遇到想要修改之前 commit 的提交信息，这里记录下怎么使用 git 修改之前已经提交的信息。

## 1 修改最近一次 commit 的信息

使用命令：git commit --amend, 进入命令模式，这是按 a 或者 i 或者 o 进入编辑模式，我们修改好 commit 信息后按 Esc 健退出编辑模式，然后: wq 保存我们编辑的信息。

最后 git push 到远程仓库

## 2 修改最近两个或者两次上的 commit 信息

比如我有两次提交，使用命令：`git rebase -i HEAD~2`

注意这里显示的顺序其实是倒序。最新的提交在最下面，最老的提交在最上面。

这里把我们要修改的 commit，这里是倒数第二次的 commit init 那个。对应的 pick 改成 e 或者 edit。退出保存。

这里会提示你使用 `git commit --amend` 去修改，改好之后用 `git rebase --continue` 完成

我们把 init 改成 init modify 再保存退出，之后用 `git rebase --continue` 完成 rebase

这时我们已经改好了倒数第二次提交信息。

提交 push 我们的修改就完成了。

【自己的实践会发现，修改那个 commit 之后所有的 commit 都被更新了】

修改前：

```Bash
F:\GitHub\test (master -> origin)
λ gl
* 767b668 Lewis Tian(2020-11-19) add 3 (HEAD -> master, origin/master)
* 19dcee6 Lewis Tian(2020-11-19) add a21
* c3735f8 Lewis Tian(2020-11-19) add ax1
* bb9fec1 Lewis Tian(2020-11-19) init
```

我们修改第二个（19dcee6）commit 的信息为 ax1：

```Bash
F:\GitHub\test (master -> origin)
λ git rebase -i HEAD~3
# pick 19dcee6add a21 -> e 19dcee6add a21

Stopped at 19dcee6...  add a21
You can amend the commit now, with

  git commit --amend

Once you are satisfied with your changes, run

  git rebase --continue

F:\GitHub\test (HEAD detached at 19dcee6)
λ git commit --amend
# add a21 -> add ax1
[detached HEAD 850c82d] add ax1
 Date: Thu Nov 19 10:21:47 2020 +0800
 1 file changed, 1 insertion(+)

F:\GitHub\test (HEAD detached at 850c82d)
λ git rebase --continue
Successfully rebased and updated refs/heads/master.

F:\GitHub\test (master -> origin)
λ gl
* cadf918 Lewis Tian(2020-11-19) add 3 (HEAD -> master)
* 850c82d Lewis Tian(2020-11-19) add ax1
* c3735f8 Lewis Tian(2020-11-19) add ax1
* bb9fec1 Lewis Tian(2020-11-19) init
```

可以看到前两个 commit 的 hash 值都变了（767b668->cadf918，19dcee6->850c82d）

所以修改需谨慎，改以前的 commit，此 commit 之后所有 commit 都会跟着变（hash 值和日期等）
