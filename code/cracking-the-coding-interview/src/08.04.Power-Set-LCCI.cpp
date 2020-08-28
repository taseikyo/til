/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 19:04:23
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> ans;
		vector<int> tmp;
		dfs(nums, 0, tmp, ans);
		return ans;
	}
	void dfs(vector<int>& nums, int cur, vector<int>& tmp,
	         vector<vector<int>>& ans) {
		ans.push_back(tmp);
		for (int i = cur; i < nums.size(); ++i) {
			tmp.push_back(nums[i]);
			dfs(nums, i + 1, tmp, ans);
			tmp.pop_back();
		}
	}
};