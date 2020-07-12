/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:10:59
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;
		while (low < high) {
			int tmp = nums[low] + nums[high];
			if (tmp == target) {
				break;
			} else if (tmp > target) {
				--high;
			} else {
				++low;
			}
		}
		return {low + 1, high + 1};
	}
};