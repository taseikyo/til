#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-10 16:14:50
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=9

TRIPLET = 1000


def main():
    for a in range(1, TRIPLET + 1):
        for b in range(a + 1, TRIPLET + 1):
            c = TRIPLET - a - b
            if a * a + b * b == c * c:
                return a * b * c


if __name__ == "__main__":
    # 31875000
    print(main())
