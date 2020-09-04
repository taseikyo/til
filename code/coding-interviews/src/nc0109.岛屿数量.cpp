/**
 * @date    2020-09-04 16:34:52
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * 判断岛屿数量
	 * @param grid char字符型vector<vector<>>
	 * @return int整型
	 */
	int ans = 0;
	// 上下左右
	vector<int> dx { -1, 1, 0, 0};
	vector<int> dy {0, 0, -1, 1};
	int solve(vector<vector<char>>& grid) {
		if (grid.empty()) {
			return 0;
		}
		int m = grid.size(), n = grid[0].size();
		vector<vector<bool>> visit(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == '1' && !visit[i][j]) {
					dfs(grid, i, j, visit);
					++ans;
				}
			}
		}
		return ans;
	}
	void dfs(vector<vector<char>>& grid, int i, int j,
	         vector<vector<bool>>& visit) {
		int m = grid.size(), n = grid[0].size();
		if (i >= m  || i < 0 || j >= n || j < 0  || visit[i][j]
		        || grid[i][j] == '0') {
			return;
		}
		visit[i][j] = true;
		for (int x = 0; x < 4; ++x) {
			dfs(grid, i + dx[x], j + dy[x], visit);
		}
	}
};