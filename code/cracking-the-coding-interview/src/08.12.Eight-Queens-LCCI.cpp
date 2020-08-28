/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 19:20:25
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<string>> res;
	vector<vector<string>> solveNQueens(int n) {
		vector<int> pre;
		dfs(n, 0, pre);
		return res;
	}
	void dfs(int n, int index, vector<int> &pre) {
		if (index == n) {
			vector<string> ans(n, string(n, '.'));
			for (int i = 0; i < n; i++) {
				ans[i][pre[i]] = 'Q';
			}
			res.push_back(ans);
			return;
		}
		for (int i = 0; i < n; i++) {
			if (isValid(n, index, i, pre)) {
				pre.push_back(i);
				dfs(n, index + 1, pre);
				pre.pop_back();
			}
		}
	}
	bool isValid(int n, int index, int num, vector<int> &pre) {
		int prenum = pre.size();
		for (int i = 0; i < prenum; i++) {
			if (num == pre[i] || abs(num - pre[i]) == index - i)
				return false;
		}
		return true;
	}
};