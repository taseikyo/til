/**
 * @date    2020-09-10 09:37:09
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * min edit cost
	 * @param str1 string字符串 the string
	 * @param str2 string字符串 the string
	 * @param ic int整型 insert cost
	 * @param dc int整型 delete cost
	 * @param rc int整型 replace cost
	 * @return int整型
	 */
	int minEditCost(string str1, string str2, int ic, int dc,
	                int rc) {
		int m = str1.size();
		int n = str2.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; i++) dp[i][0] = i * dc;
		for (int j = 0; j <= n; j++) dp[0][j] = j * ic;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				int a = dp[i - 1][j] + dc;
				int b = dp[i][j - 1] + ic;
				int c = dp[i - 1][j - 1];
				if (str1[i - 1] != str2[j - 1]) c += rc;
				dp[i][j] = min(a, min(b, c));
			}
		}
		return dp[m][n];
	}
};