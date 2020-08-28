/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-21 20:59:12
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool isPalindrome(int x) {
		if (x < 0 || (x % 10 == 0 && x != 0)) {
			return false;
		}
		int raw = x;
		long long ans = 0;
		while (x) {
			ans = ans * 10 + x % 10;
			x /= 10;
		}
		return raw == ans;
	}
};