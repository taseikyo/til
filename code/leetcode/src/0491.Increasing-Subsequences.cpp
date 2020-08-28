/**
 * @date    2020-08-25 09:27:00
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> findSubsequences(vector<int>& nums) {
		set<vector<int>> res;
		vector<int> tmp;
		dfs(nums, 0, tmp, res);
		return vector<vector<int>>(res.begin(), res.end());
	}
	void dfs(vector<int>&nums, int i, vector<int>&tmp,
	         set<vector<int>>&res) {
		if (tmp.size() >= 2) {
			res.insert(tmp);
		}
		for (int j = i; j < nums.size(); j++) {
			if (!tmp.empty() && tmp.back() > nums[j]) continue;
			tmp.push_back(nums[j]);
			dfs(nums, j + 1, tmp, res);
			tmp.pop_back();
		}
	}
};