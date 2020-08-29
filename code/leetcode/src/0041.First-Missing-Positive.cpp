/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-29 20:03:29
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int firstMissingPositive(vector<int>& nums) {
		for (int i = 0; i < nums.size(); ++i) {
			adjust(nums, i);
		}

		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] - 1 != i) return i + 1;
		}
		return nums.size() + 1;
	}

	void adjust(vector<int>& nums, int i) {
		while (nums[i] > 0 && nums[i] <= nums.size()
		        && nums[nums[i] - 1] != nums[i]) {
			swap(nums[i], nums[nums[i] - 1]);
		}
	}
};