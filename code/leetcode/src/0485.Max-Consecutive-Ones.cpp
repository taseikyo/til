/**
 * @date    2020-09-05 15:29:19
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int n = nums.size();
		if (n == 0) return 0;
		if (n == 1) return nums[0] == 1 ? 1 : 0;
		int ans = 0, i = 0, j = 0;
		while (j < n) {
			if (nums[j] == 0) {
				ans = max(ans, j - i);
				while (j < n && nums[j] == 0) ++j;
				i = j;
			}
			++j;
			if (j == n) {
				ans = max(ans, j - i);
			}
		}
		return ans;
	}
};

class Solution {
  public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int n = nums.size();
		if (n == 0) return 0;
		if (n == 1) return nums[0] == 1 ? 1 : 0;
		int ans = 0, tmp = 0;
		for (auto x : nums) {
			if (x == 1) {
				++tmp;
			} else {
				ans = max(ans, tmp);
				tmp = 0;
			}
		}
		return ans > tmp ? ans : tmp;
	}
};