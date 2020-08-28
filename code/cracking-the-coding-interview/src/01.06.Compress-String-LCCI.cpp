/**
 * @date    2020-08-13 10:46:51
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string compressString(string s) {
		if (s.size() < 2) {
			return s;
		}
		string ans;
		int cur = -1;
		int size = s.size();
		for (int i = 0; i < size - 1; ++i) {
			if (s[i] != s[i + 1]) {
				ans.push_back(s[i]);
				ans += to_string(i - cur);
				cur = i;
			}
		}
		ans.push_back(s[size - 1]);
		if (s[size - 2] != s[size - 1]) {
			ans.push_back('1');
		} else {
			ans += to_string(size - 1 - cur);
		}
		return ans.size() < s.size() ? ans : s;
	}
};