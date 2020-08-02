/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:53:57
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int first = findFirst(nums, target);
		int last = findFirst(nums, target + 1) - 1;
		if (first == nums.size() || nums[first] != target) {
			return { -1, -1};
		}
		return {first, max(first, last)};
	}

	int findFirst(vector<int>& nums, int target) {
		int l = 0, h = nums.size(); // 注意 h 的初始值
		while (l < h) {
			int m = l + (h - l) / 2;
			if (nums[m] >= target) {
				h = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}
};