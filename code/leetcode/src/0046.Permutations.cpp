/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-29 20:37:47
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> ans;
	vector<vector<int>> permute(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		dfs(nums, 0);
		return ans;
	}
	void dfs(vector<int>& nums, int cur) {
		if (cur == nums.size()) {
			ans.push_back(nums);
		}
		for (int i = cur; i < nums.size(); ++i) {
			swap(nums[i], nums[cur]);
			dfs(nums, cur + 1);
			swap(nums[i], nums[cur]);
		}
	}
};