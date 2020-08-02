/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:00:18
 * @link    github.com/taseikyo
 */

#include <stdio.h>
#include <iostream>

class Solution {
  public:
	bool judgeSquareSum(int c) {
		if (c < 0) {
			return false;
		}
		if (c == 0) {
			return true;
		}
		int i = 0, j = sqrt(c);
		while (i <= j) {
			// 溢出
			// int tmp = i * i + j * j;
			int diff = c - j * j;
			if (diff == i * i) {
				return true;
			} else if (diff < i * i) {
				--j;
			} else {
				++i;
			}
		}
		return false;
	}
};