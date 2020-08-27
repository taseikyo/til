/**
 * @date    2020-08-27 18:56:36
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> ans;
	vector<vector<int>> combine(int n, int k) {
		if (k < 1) {
			return {{}};
		}
		vector<int> tmp;
		backtrace(tmp, n, k, 1);
		return ans;
	}
	void backtrace(vector<int>& tmp, int n,
	               int k, int cur) {
		if (tmp.size() == k) {
			ans.push_back(tmp);
			return;
		}
		for (int i = cur; i <= n; ++i) {
			tmp.push_back(i);
			backtrace(tmp, n, k, i + 1);
			tmp.pop_back();
		}
	}
};