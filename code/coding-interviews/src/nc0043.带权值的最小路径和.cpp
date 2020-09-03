/**
 * @date    2020-09-03 20:22:54
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param grid int整型vector<vector<>>
	 * @return int整型
	 */
	int minPathSum(vector<vector<int> >& grid) {
		int m = grid.size(), n = grid[0].size();
		for (int i = 1; i < n; ++i) {
			grid[0][i] += grid[0][i - 1];
		}
		for (int i = 1; i < m; ++i) {
			grid[i][0] += grid[i - 1][0];
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
			}
		}
		return grid[m - 1][n - 1];
	}
};