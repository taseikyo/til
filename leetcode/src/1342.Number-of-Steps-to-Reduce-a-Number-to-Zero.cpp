/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 23:19:09
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int numberOfSteps (int n) {
		int ans = 0;
		while (n) {
			++ans;
			if (n % 2) {
				n -= 1;
			} else {
				n /= 2;
			}
		}
		return ans;
	}
};