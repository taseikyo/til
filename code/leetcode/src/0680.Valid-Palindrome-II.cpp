/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:17:14
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool validPalindrome(string s) {
		for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
			if (s[i] != s[j]) {
				return foo(s, i, j - 1) || foo(s, i + 1, j);
			}
		}
		return true;
	}

	bool foo(string &s, int i, int j) {
		while (i < j) {
			if (s[i++] != s[j--]) {
				return false;
			}
		}
		return true;
	}
};