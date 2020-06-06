#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-12 10:17:44
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=16


def main():
    return sum(int(x) for x in str(2 ** 1000))


if __name__ == "__main__":
    # 1366
    print(main())
