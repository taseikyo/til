#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-11 15:20:23
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=14

import itertools

CACHE = {}


def main():
    return max(range(1, 1000000), key=collatz_chain_length)


def collatz_chain_length(x):
    if x == 1:
        return 1
    if x % 2 == 0:
        y = x // 2
    else:
        y = x * 3 + 1
    if y in CACHE:
        return CACHE[y]
    else:
        CACHE[y] = collatz_chain_length(y) + 1
        return CACHE[y]


if __name__ == "__main__":
    # 837799
    print(main())
