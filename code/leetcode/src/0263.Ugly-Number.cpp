/**
 * @date    2020-08-27 20:46:14
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	bool isUgly(int num) {
		if (num < 1) return false;
		while (num % 2 == 0) num >>= 1;
		while (num % 3 == 0) num /= 3;
		while (num % 5 == 0) num /= 5;
		return num == 1;
	}
};