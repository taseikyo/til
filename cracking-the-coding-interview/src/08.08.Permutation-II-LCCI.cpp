/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 20:23:29
 * @link    github.com/taseikyo
 */

class Solution {
	vector<string>ans;
	void backracking(string &s, int start) {
		if (start == s.size()) {
			ans.emplace_back(s);
		}
		for (int i = start; i < s.size(); ++i) {
			swap(s[i], s[start]);
			backracking(s, start + 1);
			swap(s[i], s[start]);
		}
	}
  public:
	vector<string> permutation(string S) {
		backracking(S, 0);
		sort(ans.begin(), ans.end());
		auto it = unique(ans.begin(), ans.end());
		ans.erase(it, ans.end());
		return ans;
	}
};

class Solution {
	string s;
	int n;
	vector<int> st;
	vector<string> ans;
  public:
	vector<string> permutation(string S) {
		s = S;
		n = s.size();
		st.resize(n);
		sort(s.begin(), s.end());
		dfs(0, "");
		return ans;
	}

	void dfs(int u, string state) {
		if (u == n) {
			ans.push_back(state);
		}

		for (int i = 0; i < s.size(); i ++ ) {
			if (st[i] == 0) {
				st[i] = 1;
				state += s[i];
				dfs(u + 1, state);
				st[i] = 0;
				state.pop_back();

				while (i + 1 < s.size() && s[i + 1] == s[i]) i ++;
			}
		}
	}
};