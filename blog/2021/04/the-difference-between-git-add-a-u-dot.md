> @Date    : 2021-04-09 15:29:19
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# git add -A/git add -u/git add . 三者的区别

> 原文：https://blog.csdn.net/csm201314/article/details/78385742 [csm201314](https://blog.csdn.net/csm201314) 2017-10-29 15:34:47

- `git add -u`：将文件的修改、文件的删除，添加到暂存区。  
- `git add .`：将文件的修改，文件的新建，添加到暂存区。  
- `git add -A`：将文件的修改，文件的删除，文件的新建，添加到暂存区。

-u 就是 update 的意思，只会标记本地有改动（包括删除和修改）的已经追踪的文件

> -u, –update
> 
> Update the index just where it already has an entry matching . This removes as well as modifies index entries to match the working tree, but adds no new files
> 
> If no is given when -u option is used, all tracked files in the entire working tree are updated (old versions of Git used to limit the update to the current directory and its subdirectories).

-A 就是 all 的意思，会标记本地所有有改动（包括删除和修改）和新增的文件

> -A, –all, –no-ignore-removal
> 
> Update the index not only where the working tree has a file matching but also where the index already has an entry. This adds, modifies, and removes index entries to match the working tree.
> 
> If no is given when -A option is used, all files in the entire working tree are updated (old versions of Git used to limit the update to the current directory and its subdirectories).

**总结：**

> `git add -A` 提交所有变化
> 
> `git add -u` 提交被修改 (modified) 和被删除 (deleted) 文件，不包括新文件(new)
> 
> `git add .` 提交新文件 (new) 和被修改 (modified) 文件，不包括被删除 (deleted) 文件
