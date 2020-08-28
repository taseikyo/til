/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 16:16:38
 * @link    github.com/taseikyo
 */
// dp[i][j] 表示最大正方形的右下角，同时表示边长
int countSquares(vector<vector<int>>& A) {
	int res = 0;
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < A[0].size(); res += A[i][j++])
			if (A[i][j] && i && j)
				A[i][j] += min({A[i - 1][j - 1], A[i - 1][j], A[i][j - 1]});
	return res;
}