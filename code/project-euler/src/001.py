#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 12:07:46
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=1


def main():
    return sum([i for i in range(1, 1000) if (i % 3 == 0) or (i % 5 == 0)])


if __name__ == "__main__":
    # 233168
    print(main())
