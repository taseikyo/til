/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:20:59
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	void moveZeroes(vector<int>& nums) {
		int begin = 0, cur = 0;
		while (cur < nums.size()) {
			if (nums[cur] == 0) {
				++cur;
			} else {
				swap(nums[begin++], nums[cur++]);
			}
		}
	}
};