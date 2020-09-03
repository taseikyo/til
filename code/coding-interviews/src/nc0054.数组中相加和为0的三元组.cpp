/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 22:03:49
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int n = nums.size();
		vector<vector<int>> ans;
		for (int i = 0; i < n - 2; ++i) {
			if (i != 0 && nums[i] == nums[i - 1]) {
				continue;
			}
			help(nums, i, ans);
		}
		return ans;
	}
	void help(vector<int>& nums, int cur,
	          vector<vector<int>>& ans) {
		int n = nums.size();
		int l = cur + 1;
		int r = n - 1;
		while (l < r) {
			int tmp = nums[l] + nums[cur] + nums[r];
			if (tmp == 0) {
				ans.push_back({nums[l], nums[cur], nums[r]});
				while (l < r && nums[l] == nums[l + 1]) l++;
				while (l < r && nums[r] == nums[r - 1]) r--;
				++l, --r;
			} else if (tmp > 0) {
				while (l < r && nums[r] == nums[r - 1]) r--;
				r--;
			} else {
				while (l < r && nums[l] == nums[l + 1]) l++;
				l++;
			}
		}
	}
};