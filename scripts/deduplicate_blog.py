#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-09-14 11:32:00
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : python3.8

"""
判断某个博客的内容是否已经被保存了
用法：输入要保存的链接

最后也只能判断这个链接是否存在于某个文件，并不能
判断是否保存，所以输出是发现了；
如果都没找到，那么肯定没存；
"""

import os
import sys


def deduplicate(link):
    found = False
    for blog in os.listdir("blog"):
        if found:
            break
        with open(f"blog/{blog}", encoding="utf-8") as f:
            for line in f:
                if line.find(link) > 0:
                    found = True
                    print(
                        f"the link has been found!\nfile:\n\tblog/{blog}\ntext:\n\t{line}"
                    )
                    break
    if not found:
        print(f"{link} has not been saved.")


def main():
    if len(sys.argv) < 2:
        print("python deduplicate_blog.py xxxx.html")
    else:
        deduplicate(sys.argv[1])


if __name__ == "__main__":
    main()
