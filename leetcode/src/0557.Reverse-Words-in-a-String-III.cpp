/**
 * @date    2020-08-21 17:04:36
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string reverseWords(string s) {
		int i, j;
		i = j = 0;
		while (j < s.size()) {
			if (j == s.size() - 1 || s[j] == ' ') {
				int end = j == s.size() - 1 ? j : j - 1;
				reverse(s, i, end);
				i = j + 1;
			}
			++j;
		}
		return s;
	}
	// [i, j]
	void reverse(string& s, int i, int j) {
		while (i < j) {
			swap(s[i++], s[j--]);
		}
	}
};