/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:26:52
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int  NumberOf1(int n) {
		int ans = 0;
		while (n) {
			n &= n - 1;
			++ans;
		}
		return ans;
	}
};