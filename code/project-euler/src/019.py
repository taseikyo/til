#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-12 10:35:04
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=19

import datetime


def main():
    return sum(
        1
        for y in range(1901, 2001)
        for m in range(1, 13)
        if datetime.date(y, m, 1).weekday() == 6
    )


if __name__ == "__main__":
    # 171
    print(main())
