#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-07-12 10:24:57
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python3.7

# https://projecteuler.net/problem=17


def main():
    return sum(len(to_english(i)) for i in range(1, 1001))


def to_english(n):
    if 0 <= n < 20:
        return ONES[n]
    elif 20 <= n < 100:
        return TENS[n // 10] + (ONES[n % 10] if (n % 10 != 0) else "")
    elif 100 <= n < 1000:
        return (
            ONES[n // 100]
            + "hundred"
            + (("and" + to_english(n % 100)) if (n % 100 != 0) else "")
        )
    elif 1000 <= n < 1000000:
        return (
            to_english(n // 1000)
            + "thousand"
            + (to_english(n % 1000) if (n % 1000 != 0) else "")
        )
    else:
        raise ValueError()


ONES = [
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen",
]
TENS = [
    "",
    "",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
]

if __name__ == "__main__":
    # 21124
    print(main())
