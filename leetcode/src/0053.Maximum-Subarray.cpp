/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-13 15:35:59
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int maxSubArray(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		if (nums.size() == 1) {
			return nums[0];
		}
		int ret = nums[0];
		int sum = ret;
		for (int i = 1; i < nums.size(); ++i) {
			if (sum > 0) {
				sum += nums[i];
			} else {
				sum = nums[i];
			}
			if (sum > ret) {
				ret = sum;
			}
		}
		return ret;
	}
};