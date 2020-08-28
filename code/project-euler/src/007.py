#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-10 15:40:24
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=7

from pylib import is_prime


def main():
    count, number = 0, 2
    while True:
        if is_prime(number):
            count += 1
        if count == 10001:
            return number
        number += 1


if __name__ == "__main__":
    # 104743
    print(main())
