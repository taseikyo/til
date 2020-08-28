#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 13:45:03
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=5

import math

"""
Apparently, the smallest multiple number is the lowest common multiple (LCM) of {1, 2...20}.
LCM(x, y) = x * y / GCD(x, y)
"""


def main():
    ans = 1
    for x in range(2, 21):
        ans *= x // math.gcd(x, ans)
    return ans


if __name__ == "__main__":
    # 232792560
    print(main())
