#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-11 14:47:06
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=12

from math import sqrt


def main():
    triangle = 36
    base = 9
    while True:
        count = 1
        for x in range(2, int(sqrt(triangle)) + 1):
            if triangle % x == 0:
                count += 1
        if count >= 250:
            return triangle
        triangle += base
        base += 1


if __name__ == "__main__":
    # 76576500
    print(main())
