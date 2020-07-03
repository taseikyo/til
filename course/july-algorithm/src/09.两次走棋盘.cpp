/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 17:02:07
 * @link    github.com/taseikyo
 */

// dp[step][i][j]表示在第step步两次分别在第i行和第j行的最大得分
int MinPathSum(int a[N][N], int n) {
	int P = n * 2  - 2;// 最终的步数
	int i, j, step;
	// 不能到达的位置设置为负无穷大
	for (i = 0; i < n; ++i)
		for (j = i; j < n : ++j)
			dp[0][i][j] = -inf;
	dp[0][0][0] = a[0][0];
	for (step = 1; step <= P; ++step) {
		for (i = 0; i < n; ++i) {
			for (i = i, j < n; ++i) {
				dp[step][i][j] = -inf;
				if (!isValid(step, i, i, n)) //非法位置
					continue;
				// 对于合法的位置进行 dp
				if (i != j) {
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i - 1, j - 1,
					                     n));
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i - 1, j,
					                     n));
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i, j - 1,
					                     n));
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i, j,
					                     n));
					dp[step][i][j] += a[i][step - i] + a[j][step - j];
				} else {
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i - 1, j - 1,
					                     n));
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i - 1, j,
					                     n));
					dp[step][i][j] = max(dp[step][i][j], GetValue(step - 1, i, j,
					                     n));
					dp[step][i][j] += a[i][step -
					                       i]; // 在同一个格子里，只能加一次
				}


			}
		}
	}
	return dp[P][n - 1][n - 1];
}