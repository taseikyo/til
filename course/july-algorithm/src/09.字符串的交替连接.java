/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 16:38:27
 * @link    github.com/taseikyo
 */

public boolean IsInterleave(String s1, String s2, String s3) {
	int n = s1.length(), m = s2.length(), s = s3.length();

	// 如果长度不一致,则 s3不可能由s1和s2交错超成
	if (n + m != s)
		return false;

	boolean[][] dp = new boolean[n + 1][m + 1];
	// 在初始化边界时, 认为空串可以由空串组成, 因此dp[0][0]值为true
	dp[0][0] = true;
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < m + 1; j++) {
			if ((i - 1 >= 0 && dp[i - 1][j] == true &&
			        s1.charAT(i - 1) == s3.charAT(i + j - 1)) // 取s1字符
			        ||
			        (j - 1 >= 0 && dp[i][j - 1] == true  &&
			         s2.charAT(j - 1) == s3.charAT(i + j - 1))) // 取s2字符
				dp[i][j] = true;
			else dp[i][j] = false;
		}
	}
	return dp[n][m];
}