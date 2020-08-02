/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:17:10
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int findMin(vector<int>& nums) {
		if (nums.size() == 1) {
			return nums[0];
		}
		int l = 0, h = nums.size() - 1;
		while (l <= h) {
			int m = l + (h - l) / 2;
			if (nums[h] < nums[m]) {
				l = m + 1;
			} else if (nums[h] == nums[m]) {
				break;
			} else {
				h = m;
			}
		}
		return nums[h];
	}
};