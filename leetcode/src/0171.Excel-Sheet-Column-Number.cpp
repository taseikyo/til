/**
 * @date    2020-08-23 19:59:30
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int titleToNumber(string s) {
		int ans = 0;
		for (auto ch : s) {
			// 不加括号会溢出
			// ans = ans * 26 + ch - 'A' + 1;
			ans = ans * 26 + (ch - 'A' + 1);
		}
		return ans;
	}
};