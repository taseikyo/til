#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-07 13:17:55
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

import math


def is_prime(num):
    """return True if `num` is prime"""
    if num <= 1:
        return False
    elif num <= 3:
        return True
    elif num % 2 == 0:
        return False
    for x in range(2, int(math.sqrt(num)) + 1):
        if num % x == 0:
            return False
    return True


# A{m, n} = n(n-1)(n-2)...(n-m+1)
def Permutation(n, m):
    return math.factorial(n) // math.factorial(n - m)


# C{m, n} = A{m, n} / m!
def Combination(n, m):
    return Permutation(n, m) // math.factorial(m)
