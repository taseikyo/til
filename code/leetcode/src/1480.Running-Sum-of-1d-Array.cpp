/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 22:22:14
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> runningSum(vector<int>& nums) {
		for (int i = 1; i < nums.size(); ++i) {
			nums[i] += nums[i - 1];
		}
		return nums;
	}
};