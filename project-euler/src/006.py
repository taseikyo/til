#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-10 15:18:29
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=6

# (1 + 2 + ... 100)^2 - (1^2 + 2^2 + ... 100^2) =
# 2 * [(1*2 + 1*3 + ... 1*100) + (2*3 + 2*4 + ... 2*100 + ) + ... (99*100)]


def main():
    return 2 * sum(x * y for x in range(1, 101) for y in range(x + 1, 101))


if __name__ == "__main__":
    # 25164150
    print(main())
