#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-09-02 21:02:08
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python 3.8

"""
统计本项目中各编程语言所占比例
统计方法为最原始的按照后缀来判断 :0
"""

import os
import numpy as np
import matplotlib.pyplot as plt

IGNORE_DIRS = (".git",)


LANGS = {
    "cpp": "C++",
    "c": "C",
    "js": "Python",
    "java": "Java",
    "js": "JavaScript",
    "ts": "TypeScript",
    "go": "Go",
}


LANGS_DEATIL = {}


def get_data(path="."):
    for file in os.listdir(path):
        if file in IGNORE_DIRS:
            continue
        if os.path.isdir(f"{path}/{file}"):
            get_data(f"{path}/{file}")
        else:
            for k, v in LANGS.items():
                if file.endswith(k):
                    print(file)
                    if v in LANGS_DEATIL:
                        LANGS_DEATIL[v] += os.path.getsize(f"{path}/{file}")
                    else:
                        LANGS_DEATIL[v] = os.path.getsize(f"{path}/{file}")


def draw_image():
    results = {"coding": list(LANGS_DEATIL.values())}
    category_names = list(LANGS_DEATIL.keys())
    survey(results, category_names)

# category_names = ['Strongly disagree', 'Disagree',
#                   'Neither agree nor disagree', 'Agree', 'Strongly agree']
# results = {
#     'Question 1': [10, 15, 17, 32, 26],
#     'Question 2': [26, 22, 29, 10, 13],
#     'Question 3': [35, 37, 7, 2, 19],
#     'Question 4': [32, 11, 9, 15, 33],
#     'Question 5': [21, 29, 5, 5, 40],
#     'Question 6': [8, 19, 5, 30, 38]
# }


def survey(results, category_names):
    """
    https://blog.csdn.net/weixin_44521703/article/details/101827068
    """
    labels = list(results.keys())
    # 获取标签
    data = np.array(list(results.values()))
    # 获取具体数值
    data_cum = data.cumsum(axis=1)
    # 逐项加和
    category_colors = plt.get_cmap("RdYlGn")(np.linspace(0.15, 0.85, data.shape[1]))

    """
    在cmmap中取出五组颜色
    category_colors:
        [[0.89888504 0.30549789 0.20676663 1.        ]
         [0.99315648 0.73233372 0.42237601 1.        ]
         [0.99707805 0.9987697  0.74502115 1.        ]
         [0.70196078 0.87297193 0.44867359 1.        ]
         [0.24805844 0.66720492 0.3502499  1.        ]]
    
    """

    print(category_colors)
    # 常见颜色序列， 在cmap中取色

    fig, ax = plt.subplots(figsize=(3, 7))
    # 绘图
    # ax.invert_xaxis()
    # 使其更符合视觉习惯，index本身从下到上
    ax.yaxis.set_visible(False)
    ax.set_xticklabels(labels=labels, rotation=360)
    # 不需要可见
    ax.set_ylim(0, np.sum(data, axis=1).max())

    for i, (colname, color) in enumerate(zip(category_names, category_colors)):
        heights = data[:, i]
        # 取第一列数值
        starts = data_cum[:, i] - heights
        # 取每段的起始点
        ax.bar(labels, heights, bottom=starts, width=0.5, label=colname, color=color)
        xcenters = starts + heights / 2
        r, g, b, _ = color
        text_color = "white" if r * g * b < 0.5 else "darkgrey"
        for y, (x, c) in enumerate(zip(xcenters, heights)):
            ax.text(
                y,
                x,
                str(int(c)),
                ha="center",
                va="center",
                color=text_color,
                rotation=0,
            )
    ax.legend()
    plt.show()


if __name__ == "__main__":
    get_data()
    draw_image()
