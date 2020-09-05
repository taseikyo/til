/**
 * @date    2020-09-05 15:41:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 给定一个二进制数组，你可以最多将 1 个 0 翻转为 1，找出其中最大连续 1 的个数
// 没验证过，不知道对不对
class Solution {
  public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) return n;
		int l = 0, r = 0, count = 1, ans = 0;
		while (r < n) {
			if (nums[r] == 0) {
				if (count == 0) {
					ans = max(ans, r - l);
					while (l < r && nums[l] != 0) ++l;
					++l;
				} else {
					--count;
				}
			}
			++r;
		}
		return ans > (r - l) ? ans : r - l;
	}
};


/**
类似动态规划，使用两个变量dp0，dp1分别记录当前位置i不含有0的最大子数组长度、含一个0的最大子数组长度。
当i= 1 dp0 = dp0 +1，dp1 = dp1+1
当i =0，,dp0 = 0，dp1 = dp0 + 1.由于dp1之前已经含有一个0了
所以再遇到0需要更新成dp0（不含0的）并且加1（相当于当前dp1又含了个0），然后dp0 初始化成0（因为dp0不能含有0）
 */
int findMaxConsecutiveOnes(vector<int> &nums) {
	int dp1 = 0;
	int dp0 = 0;
	int res = -1;
	for (int i = 0; i < nums.size(); ++i) {
		if (nums[i] == 1) {
			dp1 = dp1 + 1;
			dp0 = dp0 + 1;
		} else {
			dp1 = dp0 + 1;
			dp0 = 0;
		}
		res = max(dp1, max(res, dp0));
	}
	return res;
}