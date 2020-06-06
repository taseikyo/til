#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 12:13:13
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=2


def main():
    a, b = 1, 2
    ans = b
    while b < 4000000:
        a, b = b, a + b
        if b % 2 == 0:
            ans += b
    return ans


if __name__ == "__main__":
    # 4613732
    print(main())
