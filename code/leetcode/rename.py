#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-06-06 14:32:07
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.8

"""
将空格修改为连字符

0094.Binary Tree Inorder Traversal.cpp
->
0094.Binary-Tree-Inorder-Traversal.cpp
"""

import os


def main():
    files = os.listdir("src")
    for file in files:
        os.rename(f"src/{file}", f"src/{file.replace(' ', '-')}")


if __name__ == "__main__":
    main()
