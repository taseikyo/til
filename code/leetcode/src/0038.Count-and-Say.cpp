/**
 * @date    2020-08-28 20:46:42
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string countAndSay(int n) {
		string s = "1";
		if (n < 1) {
			return "";
		} else if (n == 1) {
			return s;
		}
		for (int i = 2; i <= n; ++i) {
			string tmp;
			int cnt = 1;
			for (int i = 0; i < s.size(); ++i, ++cnt) {
				if (i == s.size() - 1 || s[i] != s[i + 1]) {
					tmp += to_string(cnt) + s[i];
					cnt = 0;
				}
			}
			s = tmp;
		}
		return s;
	}
};