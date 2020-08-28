/**
 * @date    2020-08-26 10:35:56
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<string>> ans;
	vector<vector<string>> solveNQueens(int n) {
		vector<int> v(n, -1);
		dfs(v, 0);
		return ans;
	}
	void dfs(vector<int>& v, int cur) {
		if (cur == v.size()) {
			vector<string> tmp;
			for (int i = 0; i < cur; ++i) {
				string s(cur, '.');
				s[v[i]] = 'Q';
				tmp.push_back(s);
			}
			ans.push_back(tmp);
			return;
		}
		for (int i = 0; i < v.size(); ++i) {
			bool canset = true;
			for (int j = 0; j < cur; ++j) {
				if (i == v[j] || abs(cur - j) == abs(v[j] - i)) {
					canset = false;
					break;
				}
			}
			if (canset) {
				v[cur] = i;
				dfs(v, cur + 1);
				v[cur] = -1;
			}
		}
	}
};