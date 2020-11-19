> @Date    : 2020-11-19 20:35:03
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# win10 修改 wsl2 和 docker 镜像的安装路径

- https://blog.csdn.net/lee_jackgg/article/details/106738878
- https://blog.csdn.net/fleaxin/article/details/109812090

## 查看所有分发版本

```Bash
PS D:\WSL2> wsl -l -v --all
  NAME                   STATE           VERSION
* Ubuntu-20.04           Running         2
  docker-desktop         Running         2
  docker-desktop-data    Running         2
```

注意当前目录为 `d:/WSL2` 这是我专门建立用来装 wsl2 相关文件的目录，目前有 "ubuntu20.05" "docker-desktop" "docker-desktop-data" 三个文件夹，后面有用。

## 导出镜像为 tar 文件

```Bash
wsl --export Ubuntu-20.04 ubuntu20.04.tar
wsl --export docker-desktop docker-desktop.tar
wsl --export docker-desktop-data docker-desktop-data.tar
```

## 删除当前的子系统

```Bash
wsl --unregister Ubuntu-20.04
wsl --unregister docker-desktop
wsl --unregister docker-desktop-data
```

## 重新导入并安装分发版

```Bash
wsl --import Ubuntu-20.04 d:\WSL2\ubuntu20.04 .\ubuntu20.04.tar --version 2
wsl --import docker-desktop D:\WSL2\docker-desktop\ .\docker-desktop.tar --version 2
wsl --import docker-desktop-data D:\WSL2\docker-desktop-data\ .\docker-desktop-data.tar --version 2
```

## 设置默认登陆用户为安装时用户名

```Bash
ubuntu2004 config --default-user tian
```

重新运行 docker desktop，然后 pull 一个镜像，C 盘不会变大了，因为下载的镜像在 "D:/WSL2/docker-desktop-data/ext4.vhdx" 中。

最后把之前导出的镜像删除即可。
