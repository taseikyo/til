/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-19 16:11:15
 * @link    github.com/taseikyo
 */

// https://leetcode-cn.com/problems/burst-balloons/solution/chuo-qi-qiu-by-leetcode-solution/
// dp[i][j] 表示填满开区间 (i, j) 能得到的最多硬币数，
// 边界条件是 i ≥ j−1，此时有 dp[i][j] = 0
// i < j-1 时，dp[i][j] = max{val[i]×val[k]×val[j]+dp[i][k]+dp[k][j]}
// k 从 i+i ~ j-1
class Solution {
  public:
	int maxCoins(vector<int>& nums) {
		int n = nums.size();
		vector<vector<int>> rec(n + 2, vector<int>(n + 2));
		vector<int> val(n + 2);
		val[0] = val[n + 1] = 1;
		for (int i = 1; i <= n; i++) {
			val[i] = nums[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i + 2; j <= n + 1; j++) {
				for (int k = i + 1; k < j; k++) {
					int sum = val[i] * val[k] * val[j];
					sum += rec[i][k] + rec[k][j];
					rec[i][j] = max(rec[i][j], sum);
				}
			}
		}
		return rec[0][n + 1];
	}
};

