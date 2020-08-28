#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-12 10:27:17
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=20

import math


def main():
    return sum(int(x) for x in str(math.factorial(100)))


if __name__ == "__main__":
    # 648
    print(main())
