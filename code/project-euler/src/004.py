#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 13:25:22
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=4


def main():
    return max(
        i * j
        for i in range(100, 1000)
        for j in range(100, 1000)
        if str(i * j) == str(i * j)[::-1]
    )


if __name__ == "__main__":
    # 906609
    print(main())
