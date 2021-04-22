> @Date    : 2021-04-09 16:45:41
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# win10 环境下安装 jupyter 时遇到的问题

> 原文：https://www.jianshu.com/p/bf81a345a429 [anansmile](https://www.jianshu.com/u/83d03ea50d21) 2021.03.03 17:24:20


## python 版本 3.8 安装 jupyter 遇到的问题

1. 由于内外网原因，执行 pip install jupyter 下载不了，需要 [将 pip 镜像更换到国内](https://blog.csdn.net/sinat_21591675/article/details/82770360)
2. 提示 pip 版本不对，更新 pip，更新 setuptools：python -m pip install --upgrade pip/setuptools
3. 报无 Cython 错误，安装 Cython:pip install Cython
4. 报需要 vc 14++, 下载 [路径 1](https://blog.csdn.net/qq_38161040/article/details/88203864) 或者[路径 2](https://go.microsoft.com/fwlink/?LinkId=691126)
5. 报无 stdint.h, [点击下载](https://blog.csdn.net/c465869935/article/details/81289960)
6. 报无 winpty.h, 下载 [Gohlke 集合中](https://www.lfd.uci.edu/~gohlke/pythonlibs/#pywinpty) 手动安装 _pip install pywinpty-0.5.7-cp38-none-any.whl -i [http://cmc-cd-mirror.rnd.huawei.com/pypi/simple/](http://cmc-cd-mirror.rnd.huawei.com/pypi/simple/)_，关于下载的 whl 文件重命名请参考[文章](https://www.jianshu.com/p/b8c90490b8d5)

我的版本是 3.8，一直安装不上，后来看到这个博客安装了 Cython 和 winpty 就好了：

```Bash
pip install Cython
pip install wheel
pip install pywinpty-0.5.7-cp39-cp39-win_amd64.whl
```

pywinpty-0.5.7-cp39-cp39-win_amd64.whl 是去 https://www.lfd.uci.edu/~gohlke/pythonlibs/#pywinpty 下载的
