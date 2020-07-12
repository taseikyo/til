/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 15:55:10
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	void sortColors(vector<int>& nums) {
		int begin = 0, cur = 0, end = nums.size() - 1;
		while (cur <= end) {
			if (nums[cur] == 1) {
				++cur;
			} else if (nums[cur] == 2) {
				swap(nums[cur], nums[end]);
				--end;
			} else {
				swap(nums[cur], nums[begin]);
				++begin;
				++cur;
			}
		}
	}
};