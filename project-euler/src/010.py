#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-10 16:19:28
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=10

from pylib import is_prime


def main():
    return sum(i for i in range(2, 2000000) if is_prime(i))


if __name__ == "__main__":
    # 142913828922
    print(main())
