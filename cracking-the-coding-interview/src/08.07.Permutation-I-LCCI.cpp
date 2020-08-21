/**
 * @date    2020-08-19 17:23:49
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  private:
	vector<string> res;
	void dfs(string &s, int cur) {
		if (cur == s.size()) res.emplace_back(s);
		for (int i = cur; i < s.size(); ++i) {
			swap(s[i], s[cur]);
			dfs(s, cur + 1);
			swap(s[i], s[cur]);
		}
	}
  public:
	vector<string> permutation(string S) {
		res.clear();
		dfs(S, 0);
		return res;
	}
};