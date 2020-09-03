/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 22:26:27
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * 最大正方形
	 * @param matrix char字符型vector<vector<>>
	 * @return int整型
	 */
	int solve(vector<vector<char> >& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		int maxm = 0;
		// d[i][j] 表示 (i, j) 为右下角最大的正方形的边长
		vector<vector<int>> d(row, vector<int>(col, 0));
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				if (matrix[i][j] == '1') {
					if (i == 0 || j == 0)
						d[i][j] = 1;
					else {
						d[i][j] = min(d[i - 1][j], min(d[i][j - 1], d[i - 1][j - 1])) + 1;
					}
				}
				maxm = max(maxm, d[i][j]);
			}
		return maxm * maxm;
	}
};