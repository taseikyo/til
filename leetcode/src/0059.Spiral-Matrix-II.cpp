/**
 * @date    2020-08-21 16:11:38
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> generateMatrix(int n) {
		if (n < 1) {
			return {}
		}
		if (n == 1) {
			return {1};
		}
		vector<vector<int>> ans(n, vector<int>(n));
		help(ans, 1, 0, 0, n - 1, n - 1);
		return ans;
	}
	void help(vector<vector<int>> &ans, int cur, int x1, int y1,
	          int x2, int y2) {
		if (x1 > x2 || y1 > y2) {
			return;
		}
		for (int i = y1; i <= y2; ++i) {
			ans[x1][i] = cur++;
		}
		for (int i = x1 + 1; i <= x2; ++i) {
			ans[i][y2] = cur++;
		}
		for (int i = y2 - 1; i >= y1; --i) {
			ans[x2][i] = cur++;
		}
		for (int i = x2 - 1; i > x1; --i) {
			ans[i][y1] = cur++;
		}
		help(ans, cur, x1 + 1, y1 + 1, x2 - 1, y2 - 1);
	}
};