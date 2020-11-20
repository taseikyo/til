> @Date    : 2020-11-20 17:25:30
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 将代码同时 push 到 github 和码云

> 原文：https://www.jianshu.com/p/a44c7636164b 2017.10.25 23:31:13 [沙子硅](https://www.jianshu.com/u/c7d9eb314548)

**首先，要明白一点：在我们执行了 git add . 指令之后，我们的代码是被放到了本地仓库，而且一个本地仓库可以对应多个远程仓库。**

有了上面的概念之后，那么下面就很好进行了。

在这里做一个假设：我的 github 和码云上面都已经初始化好了 reposity，而且本地的代码最开始 clone 自码云（其实这里无所谓了，也可以是来自 github，当然你也可以直接在本地初始化这只取决于个人习惯）

接下来，我们就要开始配置了。

通过 `git remote add <name> <url-of-remote>` 指令来添加远程仓库。

- name 是远程仓库的别名，便于区分不同的远程仓库。
- url-of-remote 是我们的远程仓库链接，就是平时看到的以 ".git" 为后缀的链接啦！

比如，我想添加 github 的远程仓库，并且取名为 github：

```Bash
git remote add github https://github.com/gongqingfeng/Drcom.git
```

好，来看一下我们刚刚添加好的仓库：

```
git remote -v
```

从图中我们可以看到，我的 github 远程仓库已经被成功添加了。而且默认的码云远程仓库被命名为 origin，这也是为什么我们平时 push 代码的时候要使用 git push orgin master 了。

恩，接下来我们就准备把代码推送到 github 和码云吧！

1. 添加代码到本地仓库

```Bash
git add .
```

2. 提交并添加描述

```Bash
git commit -m "first commit"
```

3. push 到相应的仓库

- push 到 github

```Bash
git push github master
```

- push 到码云

```Bash
git push origin master
```

这样我们就把代码推送到 github 和码云上了。 
