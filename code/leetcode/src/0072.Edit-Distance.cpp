/**
 * @date    2020-09-10 09:29:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// https://www.cnblogs.com/flix/p/13596911.html
// dp[i][j] 表示 str[0,...,i-1] 到 str[0,...,j-1] 的最小代价
// dp[i][j] 可以从 dp[i-1][j]、dp[i][j-1] 和 dp[i-1][j-1] 转化而来
// 我们设置 3 个变量：
// 		a = dp[i-1][j] + dc
// 		b = dp[i][j-1] + ic
// 		c 从 dp[i-1][j-1] 推导而来，str1[i-1]==str2[j-1] 时，c = dp[i-1][i-1]，否则 c = dp[i-1][j-1] + rc
// 然后 dp[i][j] = min(a, b, c)
class Solution {
  public:
	int minDistance(string str1, string str2) {
		int m = str1.size();
		int n = str2.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; i++) dp[i][0] = i;
		for (int j = 0; j <= n; j++) dp[0][j] = j;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				int a = dp[i - 1][j] + 1;
				int b = dp[i][j - 1] + 1;
				int c = dp[i - 1][j - 1];
				if (str1[i - 1] != str2[j - 1]) c += 1;
				dp[i][j] = min(a, min(b, c));
			}
		}
		return dp[m][n];
	}
};