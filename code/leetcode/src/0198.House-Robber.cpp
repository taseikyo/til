/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 16:03:19
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int rob(vector<int>& nums) {
		int n = nums.size(), pre = 0, cur = 0;
		for (int i = 0; i < n; i++) {
			int temp = max(pre + nums[i], cur);
			pre = cur;
			cur = temp;
		}
		return cur;
	}
};