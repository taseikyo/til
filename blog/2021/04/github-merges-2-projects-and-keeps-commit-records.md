> @Date    : 2021-04-09 15:06:38
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# GitHub 合并 2 个项目并保留 commit 记录

> 原文：https://blog.csdn.net/u010887744/article/details/72853894 [Z小繁](https://zxiaofan.blog.csdn.net) 2017-06-03 19:19:27

GitHub 有两个项目 Pro1 和 Pro2，现打算将 Pro2 整个项目移动到 Pro1，并保留 2 个项目的 commit 记录。

移动前 Pro1 目录结构为：文件 

```Bash
- Pro1.txt
- Pro123
- README.md
- pro1dir/
```

项目 Pro2 类似

移动后目录结构为 `pro/Pro1/*`；`pro/Pro2/*`（Pro1 重命名为 pro）。

建议新建测试项目 Pro1、Pro2 熟悉一下流程，或者备份原有项目，避免误操作产生意料之外的效果。

## 1、clone 项目 Pro1 到本地

```BAsh
git clone https://github.com/zxiaofan/Pro1.git
cd Pro1
```

## 2、在 Pro1 项目根目录新建文件夹 Pro1，并将原 Pro1 项目所有文件移动至 `Pro1/` 下（如果不需要完全区别两个项目可忽略）

```Bash
mkdir Pro1
cd Pro1
# 输入描述信息（move Pro1 to new dir）
vim pro1.txt
```

如果是 GitHub 网页创建新文件，则 create new file -> 文件名框中输入文件夹名 `Pro1/`（有个斜杠），在输入文件名即可。

移动所有文件（夹）到新文件夹 Pro1

```Bash
cd ..
mv Pro123 README.md pro1dir/ Pro1
```

## 3、提交所有变更到 GitHub

将文件的修改、删除、新建添加到暂存区

（注意区别：`git add -u`：将文件的修改、文件的删除，添加到暂存区；`git add .`：将文件的修改，文件的新建，添加到暂存区）

```Bash
git add -A
git status
git commit -m "move Pro1 all files to new dir"
git push
```

## 4、移动项目 Pro2 的所有内容到 Pro1

### 将新项目添加到旧项目中

`git remote add Pro2 https://github.com/zxiaofan/Pro2.git`

### 校验是否添加成功

```Bash
git remote -v

Pro2 https://github.com/zxiaofan/Pro2.git (fetch)
Pro2 https://github.com/zxiaofan/Pro2.git (push)
origin https://github.com/zxiaofan/Pro1.git (fetch)
origin https://github.com/zxiaofan/Pro1.git (push)
```

### 获取新项目内容

`git fetch Pro2`

### 合并新项目 Pro2 到本地项目 Pro1

`git merge Pro2/master`

Note 如果报错：fatal: refusing to merge unrelated histories

此错误出现在 2.9.0 版本后，在命令后添加执行参数 `--allow-unrelated-histories` 即可

`git merge Pro2/master --allow-unrelated-histories`

会提示你输入 merge 信息：比如输入：`mergee Pro2 to Pro1`

参考操作 2，将 Pro2 的所有内容移动到新建文件夹 Pro2 中。

## 5、参考操作 3，提交所有变更到 GitHub

## 6、项目重命名

前往 github 官网，在项目 Pro1 的 Settings 中重命名 Pro1 为 Pro。

Note：Pro1 重命名为 Pro 后，原 Pro1 的地址将重定向到新的 Pro 项目的地址。

至此 2 个 github 项目合并完毕。

可参考本人合并后的项目：https://github.com/zxiaofan/springStudy ，该项目是有 SpringBootStudy、SpringDataStudy 两个项目合并到 chapter（合并后更名为 SpringStudy）项目，保留了原有的所有 commit 记录。
