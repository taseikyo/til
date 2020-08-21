/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-21 20:54:15
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int uniquePaths(int m, int n) {
		int mat[m][n];
		for (int i = 0; i < n; ++i) {
			mat[0][i] = 1;
		}
		for (int i = 0; i < m; ++i) {
			mat[i][0] = 1;
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 1;j < n; ++j) {
				mat[i][j] = mat[i-1][j] + mat[i][j-1];
			}
		}
		return mat[m - 1][n - 1];
	}
};