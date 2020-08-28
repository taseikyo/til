/**
 * @date    2020-08-22 17:17:21
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int threeSumClosest(vector<int>& nums, int target) {
		int ans = nums[0] + nums[1] + nums[2];
		int n = nums.size();
		sort(nums.begin(), nums.end());
		for (int i = 0; i < n - 2; ++i) {
			help(nums, target, i, ans);
			if (ans == target) {
				return target;
			}
		}
		return ans;
	}
	void help(vector<int>& nums, int target, int cur, int &ans) {
		int n = nums.size();
		int l = cur + 1;
		int r = n - 1;
		while (l < r) {
			int tmp = nums[l] + nums[r] + nums[cur];
			if (abs(tmp - target) < abs(ans - target)) {
				ans = tmp;
			}
			if (tmp > target) {
				--r;
			} else if (tmp < target) {
				++l;
			} else {
				ans = target;
				return ;
			}
		}
	}
};