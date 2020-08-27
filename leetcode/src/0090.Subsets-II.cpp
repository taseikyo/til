/**
 * @date    2020-08-27 18:45:16
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<vector<int>> ans;
		vector<int> tmp;
		sort(nums.begin(), nums.end());
		help(nums, tmp, ans, 0);
		return ans;
	}
	void help(vector<int>& nums, vector<int>& tmp,
	          vector<vector<int>>& ans, int cur) {
		ans.push_back(tmp);
		for (int i = cur; i < nums.size(); ++i) {
			if (i > cur and nums[i] == nums[i - 1])
				continue;
			tmp.push_back(nums[i]);
			help(nums, tmp, ans, i + 1);
			tmp.pop_back();
		}
	}
};