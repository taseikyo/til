#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-06-07 16:05:08
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : $Id$

"""
将当前目录下所有 md 文档的图片路径补全

-[xxx.jpg] => ![](../images/xxx.jpg)
"""


import os


def main():
	files = os.listdir()
	for file in files:
		if not file.endswith("md"):
			continue
		with open(file, encoding="utf-8") as f:
			lines = f.readlines()

		for x, y in enumerate(lines):
			if y.find("-[") >= 0:
				lines[x] = f"![](../images/{y[2:-2]})"
		with open(file, "w", encoding="utf-8") as f:
			f.write("".join(lines))


if __name__ == '__main__':
	main()