/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 22:36:17
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int xorOperation(int n, int start) {
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans ^= start + 2 * i;
		}
		return ans;
	}
};