#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-06-22 21:09:26
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.8

"""
统计对应 tag 下完成了多少题

如果不输入参数则查询所有 tag，如果输入参数则查询对应 tag
另外如果输入参数为数字则会查询对应题号是否完成

python count.py
    - 查询所有

python count.py tree
    - 查询 树

python count.py tag-array
    - 查询 数组

也就是说 tag 前缀可加可不加


python count.py 1469
You have not finished #1469 yet.
"""

import os
import sys


def search(num):
    """
    搜索 num 对应题是否存在
    """
    cpp_files = [x for x in os.listdir("src") if x.endswith("cpp")]

    prefix = f"{int(num):04}"
    for file in cpp_files:
        if file.startswith(prefix):
            print(file)
            return

    print(f"You have not finished #{num} yet.")


def html2md():
    """
    这个 html 指的是用浏览器打开之后复制了格式好之后的文件，而不是直接保存的那个
    """
    html_files = [x for x in os.listdir("tag") if x.endswith("html")]
    for file in html_files:
        with open(f"tag/{file}", encoding="utf-8") as f:
            lines = f.readlines()

        with open(f"tag/{os.path.splitext(file)[0]}.md", "w", encoding="utf-8") as f:
            f.write(f"{file.split('-')[-1].split('.')[0]}\n---\n")
            for index, _ in enumerate(lines[::3]):
                num = lines[index * 3]
                title = lines[index * 3 + 1]
                diff = lines[index * 3 + 2].replace("%", "%\t")
                f.write(f"{num[:-1]}\t{title[:-1]}\t{diff}")

        os.remove(f"tag/{file}")


def count(path):
    """
    查询某一种 tag 的信息
    返回该 tag 的总题数和已完成数
    """
    if not os.path.exists(path):
        print("Input tag error!")
        return

    with open(path, encoding="utf-8") as f:
        lines = f.readlines()

    cpp_files = [x for x in os.listdir("src") if x.endswith("cpp")]

    all_nums = len(lines)
    finished_nums = 0

    info = f"{lines[0][:-1]} info:"
    print(f"{info}\n{'='*len(info)}")

    for line in lines[2:]:
        x, y = line.split("\t")[:2]
        cpp = f"{int(x):04}.{y.replace(' ', '-')}.cpp"
        if cpp in cpp_files:
            print(f"√ {cpp}")
            finished_nums += 1
        else:
            print(f"× {cpp}")

    print(f"You have solved {finished_nums}/{len(lines)-2} {lines[0][:-1]} problems.\n")

    return all_nums, finished_nums


def count_all():
    """
    查询所有 tag 信息
    """
    tag_files = [x for x in os.listdir("tag") if x.startswith("tag")]

    all_tag_nums = 0
    all_finished_nums = 0
    for file in tag_files:
        all_nums, finished_nums = count(f"tag/{file}")
        all_tag_nums += all_nums
        all_finished_nums += finished_nums

    print(f"In general, you have solved {all_finished_nums}/{all_tag_nums} problems.\n")


if __name__ == "__main__":
    html2md()
    if len(sys.argv) > 1:
        path = sys.argv[1]
        if path.startswith("tag"):
            count(f"tag/{path}.md")
        elif path.isdigit():
            search(path)
        else:
            count(f"tag/tag-{path}.md")
    else:
        count_all()
