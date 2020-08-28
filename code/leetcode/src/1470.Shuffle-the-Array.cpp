/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 22:28:49
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> shuffle(vector<int>& nums, int n) {
		vector<int> ans(2 * n);
		for (int i = 0, j = 0; i < n; ++i, j = j + 2) {
			ans[j] = nums[i];
			ans[j + 1] = nums[n + i];
		}
		return ans;
	}
};