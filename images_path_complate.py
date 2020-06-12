#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-06-07 16:05:08
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.8

"""
将当前目录下所有 md 文档的图片路径补全
由于我将左右的图片放到根目录的 images 目录下
不同目录下的 md 文档相对于整个目录的相对路径是不同的

-[xxx.jpg] => ![](../images/xxx.jpg)
"""

import os


def ipc(path=".", depth=0):
    """
    根据 depth 推算相对于根目录的位置
    """
    files = os.listdir(path)
    for file in files:
        if file == ".git":
            continue
        if os.path.isdir(f"{path}/{file}"):
            ipc(f"{path}/{file}", depth+1)
        if file.endswith("md"):
            print(f"{path}/{file} {depth}")
            with open(f"{path}/{file}", encoding="utf-8") as f:
                lines = f.readlines()
            for x, y in enumerate(lines):
                if y.find("-[") >= 0:
                    lines[x] = f"![]({'../'*depth}images/{y[2:-2]})"
                    print(lines[x])
            with open(f"{path}/{file}", "w", encoding="utf-8") as f:
                f.write("".join(lines))


if __name__ == "__main__":
    ipc()
