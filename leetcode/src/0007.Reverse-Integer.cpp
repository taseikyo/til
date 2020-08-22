/**
 * @date    2020-08-22 21:23:21
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int reverse(int x) {
		long long ret = 0;
		int MAX = 2147483647;
		int MIN = -2147483648;
		while (x) {
			if (ret * 10 > MAX || x % 10 + ret * 10 > MAX
			        || ret * 10 < MIN || x % 10 + ret * 10 < MIN) {
				return 0;
			}
			ret = x % 10 + ret * 10;
			x /= 10;
		}
		return ret;
	}
};