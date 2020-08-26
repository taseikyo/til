/**
 * @date    2020-08-26 20:54:14
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int trailingZeroes(int n) {
		int count = 0;
		while (n) {
			count += n / 5;
			n /= 5;
		}
		return count;
	}
};