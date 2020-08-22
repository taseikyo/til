/**
 * @date    2020-08-22 20:36:30
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int search(vector<int>& nums, int target) {
		int l  = 0, r = nums.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (nums[mid] == target) {
				return mid;
			} else if (nums[mid] < nums[r]) {
				if (nums[mid] < target && target <= nums[r]) {
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			} else {
				if (nums[r] <= target && target < nums[mid]) {
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
		}
		return -1;
	}
};