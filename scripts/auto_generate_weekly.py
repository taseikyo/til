#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-07-25 17:23:17
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python 3.8.5

import os
import time
import datetime

TITLE_TABLE = {}
TIME_TABLE = []
DICT = [
    "blog",
    "book",
    "course",
    "cpp",
    "leetcode",
    "python",
]


def timestamp_to_time(timestamp):
    time_struct = time.localtime(timestamp)
    return time.strftime("%Y-%m-%d %H:%M:%S", time_struct)


def read_title_table_from_readme():
    """
    从 README 中获取文件的标题
    若是从文件内获取可能因为创建时的格式问题
    而无法统一代码
    """
    with open("README.md", encoding="utf-8") as f:
        for line in f:
            if line.find("](") > 0:
                foo = line.split("](")
                title = foo[0].split("[")[-1]
                filename = foo[1][:-2].split("/")[-1]
                if filename:
                    TITLE_TABLE[filename] = title

    return False if TITLE_TABLE else True


def read_create_file_time():
    """
    获取指定目录文件的创建时间
    """
    for folder in DICT:
        for file in os.listdir(folder):
            if os.path.isdir(f"{folder}/{file}"):
                pass
            else:
                file_time = timestamp_to_time(os.path.getctime(f"{folder}/{file}"))
                year, month, day = [int(i)
                                    for i in file_time.split(" ")[0].split("-")]
                print(file, month, day)


def get_files_within_7days(path="."):
    for file in os.listdir(path):
        filepath = f"{path}/{file}"
        if os.path.isdir(filepath):
            if file in (".git", "images", "leetcode", "coding-interviews"):
                continue
            get_files_within_7days(filepath)
        else:
            today = datetime.datetime.today()
            offset = datetime.timedelta(days=-7)
            last_week_date = (today + offset)
            last_week_date_unix = time.mktime(last_week_date.timetuple())
            file_create_time = os.path.getctime(filepath)
            if file_create_time >= last_week_date_unix:
                time_array = time.localtime(file_create_time)
                file_create_time = time.strftime("%Y-%m-%d %H:%M:%S", time_array)
                print(filepath, file_create_time)


def main():
    if read_title_table_from_readme():
        return
    # print(TITLE_TABLE)
    read_create_file_time()


if __name__ == "__main__":
    get_files_within_7days()
    # main()
