/**
 * @date    2020-08-22 19:55:51
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.size() < 1) {
			return {};
		} else if (matrix.size() == 1) {
			return matrix[0];
		}
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> ans;
		help(matrix, ans, 0, 0, m - 1, n - 1);
		return ans;
	}
	void help(vector<vector<int>>& matrix, vector<int> &ans,
	          int x1, int y1,
	          int x2, int y2) {
		if (x1 > x2 || y1 > y2) {
			return;
		}
		for (int i = y1; i <= y2; ++i) {
			ans.push_back(matrix[x1][i]);
		}
		for (int i = x1 + 1; i <= x2; ++i) {
			ans.push_back(matrix[i][y2]);
		}
		for (int i = y2 - 1; i >= y1 && x2 > x1; --i) {
			ans.push_back(matrix[x2][i]);
		}
		for (int i = x2 - 1; i > x1 && y2 > y1; --i) {
			ans.push_back(matrix[i][y1]);
		}
		help(matrix, ans, x1 + 1, y1 + 1, x2 - 1, y2 - 1);
	}
};