/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:23:05
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int singleNumber(vector<int>& nums) {
		int x = 0;
		for (auto i: nums) {
			x ^= i;
		}
		return x;
	}
};