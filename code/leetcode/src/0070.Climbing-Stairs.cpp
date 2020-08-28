/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-15 22:36:00
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int dp[46] = {0, 1, 2, 3};
	int climbStairs(int n) {
		if (n <= 3) {
			return n;
		}
		for (int i = 4; i <= n; ++i) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};