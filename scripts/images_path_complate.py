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
@2020/12/15
由于我将整个 repo 结构修改了下，将图片（images）和博客（blog）的文件
按照【年-月-文件名】存放，使得此脚本功能有点问题，因为图片不再以 images
为根目录存放，所以需要找到确切的位置
目前使用一个简单逻辑，显然要补全的 md 和图片是同一个月（埋的坑不算）
那么直接增加年份和月份即可
"""

import os
import time


def ipc(path=".", depth=0):
    """
    根据 depth 推算相对于根目录的位置
    """
    files = os.listdir(path)
    for file in files:
        if file == ".git":
            continue
        if os.path.isdir(f"{path}/{file}"):
            ipc(f"{path}/{file}", depth + 1)
        if file.endswith("md"):
            # 发现了 tag 才会修改
            tag = False
            with open(f"{path}/{file}", encoding="utf-8") as f:
                lines = f.readlines()
            for x, y in enumerate(lines):
                if y.find("-[") == 0:
                    tag = True
                    lines[x] = f"![]({'../'*depth}images/{time.strftime('%Y/%m', time.localtime())}/{y[2:-2]})\n"
            if tag:
                print(f"{path}/{file} {depth}")
                with open(f"{path}/{file}", "w", encoding="utf-8") as f:
                    f.write("".join(lines))


if __name__ == "__main__":
    ipc()
