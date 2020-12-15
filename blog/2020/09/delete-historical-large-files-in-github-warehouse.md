> @Date    : 2020-09-24 20:43:35
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# GitHub 仓库中删除历史大文件

> 原文：https://blog.csdn.net/qq_26662401/article/details/108214780 作者：[Galloping-Vijay](https://me.csdn.net/qq_26662401) 2020-07-31 17:41:30

【建议在 git-bash 中操作，在 cmder 中操作的话，第二步的 sort 会出问题】

## 查看 git 文件对象大小

git count-objects -v

## 列出体积最大的 top10

```bash
git verify-pack -v .git/objects/pack/pack-*.idx | sort -k 3 -g | tail -10
# 4bdc96af2540a6002a60e0f8026ac6edb8ceec7f blob   2104539 2103812 68220097
# bcaab23744d18bf7d80e2914a4820e199954b7a7 blob   2681512 2679930 52983447
# d0dd82d41145885996285a67d119862256e09b3d blob   2689821 2685468 70323909
```

## 查看具体文件名称

```bash
git rev-list --objects --all | grep <commit-id>
# 栗子： git rev-list --objects --all | grep bcc72e78c11b79c3744ae6b0cc36806b6d02dde5
# 结果： 4bdc96af2540a6002a60e0f8026ac6edb8ceec7f public/images/background/bg4.jpg
```

## 清除该文件
 
```bash
git filter-branch --force --index-filter 'git rm --cached -r --ignore-unmatch file_you_want_to_delete' --prune-empty --tag-name-filter cat -- --all
# 栗子：git filter-branch --force --index-filter "git rm --cached --ignore-unmatch 'public/images/background/bg4.jpg'"  --prune-empty --tag-name-filter cat -- --all
```

## 清空 git 历史

```bash
rm -rf .git/refs/original/
git reflog expire --expire=now --all
git gc --prune=now
git gc --aggressive --prune=now
```

## 如果这一步有权限不足的问题，需要手动到 github 上将 master 分支的保护去掉

```bash
git push origin master --force
```

## 清理远程仓库

```bash
git remote prune origin
```
