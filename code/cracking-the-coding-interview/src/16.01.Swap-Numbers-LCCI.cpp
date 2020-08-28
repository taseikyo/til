/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 22:07:36
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> swapNumbers(vector<int>& nums) {
		nums[0] = nums[0] - nums[1];
		nums[1] = nums[1] + nums[0];
		nums[0] = nums[1] - nums[0];
		return nums;
	}
};