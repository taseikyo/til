/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 22:40:56
 * @link    github.com/taseikyo
 */

// 8.51% 太惨了
class Solution {
  public:
	int searchInsert(vector<int>& nums, int target) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			if (nums[i] >= target) {
				return i;
			}
		}
		return nums.size();
	}
};

class Solution {
  public:
	int searchInsert(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;

		while (low <= high) {
			int mid = low + (high - low) / 2;

			if (nums[mid] < target)
				low = mid + 1;
			else
				high = mid - 1;
		}
		return low;
	}
};