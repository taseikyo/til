/**
 * @date    2020-09-03 19:29:53
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param x int整型
	 * @return int整型
	 */
	int reverse(int x) {
		int ans = 0;
		bool sign = 0;
		if (x < 0) {
			sign = 1;
			x = -x;
		}

		while (x) {
			ans += ans * 10 + x % 10;
			x /= 10;
		}
		return sign ? -ans : ans;
	}
};