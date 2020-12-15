> @Date    : 2020-07-20 15:30:06
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 从 7z 压缩包中读取文件

最简单的是解压然后读，最后删掉，如：

```python
import os
# scoop install 7zip
os.system("7z x archive.7z -otmp")
for file in os.listdir("tmp"):
	# read `file`
	os.remove(f"tmp/{file}")
os.rmdir("tmp")
```

然后今天发现了一个库 [libarchive](https://pypi.org/project/libarchive/)，可以直接读：

```python
import libarchive.public

with libarchive.public.file_reader('test.7z') as e:
    for entry in e:
        with open('/tmp/' + str(entry), 'wb') as f:
            for block in entry.get_blocks():
                f.write(block)
```

对于在 Ubuntu 上安装，大概两步就 OK 了：

```bash
apt-get install libarchive-dev
pip install libarchive
``` 

但是，在 Windows 上使用有 [问题](https://github.com/dsoprea/PyEasyArchive/issues/27)，需要手动安装 libarchive 库，在这个 issue 下面有人给出了操作过程，挺麻烦的，想想还是直接用原来的方法吧。

[@ganego](https://github.com/ganego):

> Python is a multi-platform programming language and as such libraries should also adhere to this concept. This library unfortunately does not work on most computers because it cannot find the libraries on Windows.
> 
> I will now explain how to compile libarchive.dll, so that one can install this python libarchive package.
> 
> * Get the x64 installer from https://www.msys2.org/ and run it.
> * Go to the installation folder and run `mingw64.exe`.
> * Run `pacman -Syu`, restart the shell and run `pacman -Su`.
> * Install minGW-64 via `pacman -S mingw-w64-x86_64-toolchain`.
> * Install minGW-64-cmake (not normal cmake, as this will lack minGW generators) via `pacman -S mingw-w64-x86_64-cmake`.
> * Install libxml2 via `pacman -S mingw-w64-x86_64-libxml2`.
> * Restart the shell.
> * Download and extract the libarchive source: https://github.com/libarchive/libarchive/releases
> * In the msys2 shell navigate to the extraced folder. You can access Windows paths via `cd /c/folder/subfolder` for `c:\folder\subfolder`.
> * Create makefiles via `cmake . -G "MinGW Makefiles"`. You might have to run this twice, as the first time you might get an error about sh.exe.
> * Compile via `mingw32-make.exe`.
> * `libarchive.dll` is now in `<libarchive_source\bin\libarchive.dll`.
> * In order to use this .dll you also need other dlls from the `<msys2>\mingw64\bin` folder. Copy those .dlls to the libarchive.dll folder:
> * libbz2-1.dll
> * libexpat-1.dll
> * libiconv-2.dll
> * liblz4.dll
> * liblzma-5.dll
> * libnettle-7.dll
> * libxml2-2.dll
> * libzstd.dll
> * zlib1.dll
> 
> Now that you got all those .dlls in one place, you have to make sure, the installer finds them when running `pip`:
> 
> * Bascially they have to be inside PATH, so you could copy them to `C:\Windows\System32\`, which would be the easiest way.
> * Finally you should be able to run `pip install libarchive` and everything works.
> 
> _Alternatively_, install python libarchive and the put the .dll files into your program/script folder where you need libarchive:
> 
> * Run `cmd` and execute `set Path=%PATH%;<libarchive_source>\bin` (replace the <...> part). Do not add any quotation marks, even if the path has spaces. This just adds to the PATH for this cmd window, not the system PATH.
> * Run `pip install libarchive`.
> * Copy all .dll files into the folder where your .py file is and add this to the top of your script (above the libarchive import): `os.environ["PATH"] += os.pathsep + os.path.dirname(os.path.abspath(__file__))`. This appends the PATH variable inside your script (not system PATH) to include the folder the .py is in. In case you want to distribute the script you should probably choose this way.
> 
> Please add some note to the PyPI repository and the github page linking to this guide or distribute a version that works on all OS.
> Thank you


