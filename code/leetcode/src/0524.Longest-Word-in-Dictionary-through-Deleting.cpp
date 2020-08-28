/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:24:54
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	string findLongestWord(string s, vector<string>& d) {
		string ans;
		for (auto i : d) {
			int l1 = ans.size(), l2 = i.size();
			if (l1 > l2 || (l1 == l2 && ans.compare(i) < 0)) {
				continue;
			}
			if (foo(s, i)) {
				ans = i;
			}
		}
		return ans;
	}
	// s 能否删除一些字符得到 i
	bool foo(string& s, string& t) {
		int i = 0, j = 0;
		while (i < s.size() && j < t.size()) {
			if (s[i] == t[j]) {
				++j;
			}
			++i;
		}
		return j == t.size();
	}
};