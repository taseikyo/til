/**
 * @date    2020-09-09 20:27:50
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	// 上下左右
	vector<int> dx{ -1, 1, 0, 0};
	vector<int> dy{0, 0, -1, 1};
	int ans = 1;
	int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
			return 0;
		}
		int m = matrix.size(), n = matrix[0].size();
		// i, j 这个点最长路径
		vector<vector<int>> dp(m, vector<int>(n, 1));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
                if (dp[i][j] > 1) {
					continue;
				}
				dfs(matrix, dp, i, j);
			}
		}
		return ans;
	}
	int dfs(vector<vector<int>>& matrix,
	        vector<vector<int>>& dp, int x, int y) {
		int m = matrix.size(), n = matrix[0].size();
		int ret = 0;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if ((nx >= 0 && nx < m) && (ny >= 0 && ny < n)) {
				if (matrix[nx][ny] > matrix[x][y]) {
					if (dp[nx][ny] > 1) {
						ret = max(ret, dp[nx][ny]);
					} else
						ret = max(ret, dfs(matrix, dp, nx, ny) + 1);
				}
			}
		}
        
		dp[x][y] += ret;
        ans = max(ans, dp[x][y]);
		return ret;
	}
};