/**
 * @date    2020-08-22 20:34:48
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() == 0) {
			return "";
		}
		if (strs.size() == 1) {
			return strs[0];
		}
		string pre = help(strs[0], strs[1]);
		if (pre.empty()) {
			return "";
		}
		for (int i = 2; i < strs.size(); ++i) {
			pre = help(strs[i], pre);
			if (pre.empty()) {
				return "";
			}
		}
		return pre;
	}
	string help(string& s1, string& s2) {
		int n = min(s1.size(), s2.size());
		int cur = -1;
		while (++cur < n) {
			if (s1[cur] != s2[cur]) {
				break;
			}
		}
		return string(s1.begin(), s1.begin() + cur);
	}
};