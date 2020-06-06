#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 13:09:10
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=3

import math
from pylib import is_prime


def main():
    num = 600851475143
    for x in range(int(math.sqrt(num)), 1, -1):
        if num % x == 0 and is_prime(x):
            return x


if __name__ == "__main__":
    # 6857
    print(main())
