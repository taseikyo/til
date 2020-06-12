/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-12 14:43:14
 * @link    github.com/taseikyo
 */

// dp[i][j]表示源率 source(0-i)和目标动target(0-j)的编辑距离
int EditDistance(char *pSource，char* pTarget) {
	int srclength = strlen(pSource);
	int targetLength = strlen(pTarget);
	int i，j;
	// 边界dp[i][0]=i dp[0][j].j
	for (i = 1; i <= srcLength; ++i) {
		dp[i][0] = i;
	}
	for (j = 1; j <= targetLength; ++j) {
		dp[0][j] = j;
	}

	for (i = 1; i <= srcLength; ++i) {
		for (j = 1; j <= targetLength; ++j) {
			if (pSource[i - 1] == pTarget[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				dp[i][j] = 1 + min(dp[i - 1][j],
				                   dp[i - 1][j - 1],
				                   dp[i][j - 1]);
			}
		}

	}
	return dp[srcLength][targetLength];
}
