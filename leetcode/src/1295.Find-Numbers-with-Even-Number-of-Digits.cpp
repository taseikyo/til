/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-13 15:44:04
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int findNumbers(vector<int>& nums) {
		int ret = 0;
		for (auto i : nums) {
			int cnt = 0;
			while (i) {
				i >>= 1;
				++cnt;
			}
			if (cnt % 2 == 0) {
				++ret;
			}
		}
		return ret;
	}
};