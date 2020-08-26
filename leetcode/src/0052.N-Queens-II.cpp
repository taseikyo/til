/**
 * @date    2020-08-26 09:51:52
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int ans = 0;
	int totalNQueens(int n) {
		if (n < 2) {
			return n;
		}
		vector<int> v(n, -1);
		dfs(v, 0);
		return ans;
	}
	void dfs(vector<int>& v, int cur) {
		if (cur == v.size()) {
			++ans;
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