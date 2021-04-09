> @Date    : 2021-03-25 22:07:02
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Ubuntu 下 git 版本升级

> https://blog.csdn.net/qq_37925382/article/details/104676336 [-CapricornusW](https://blog.csdn.net/qq_37925382) 2020-03-05 16:07:44

## 1、查看 git 版本

```Bash
git --version
```

## 2、升级 Git

```Bash
# 更新源
sudo apt update
# 安装 PPA 需要的依赖
sudo apt install software-properties-common
# 向 PPA 中添加 git 的软件源
sudo add-apt-repository ppa:git-core/ppa
sudo apt-get update
sudo apt-get install git
```
