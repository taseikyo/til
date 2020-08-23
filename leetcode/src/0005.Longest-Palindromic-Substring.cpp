/**
 * @date    2020-08-23 15:47:49
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	void help(const string &s, int left, int right, int& start,
	          int& maxlen) {
		while (left >= 0 && right < s.size()) {
			if (s[left] != s[right]) break;
			--left;
			++right;
		}
		// 退出循环时，串的区间实际上是[left+1,right-1]
		if (right - left - 1 > maxlen ) {
			// 区间长度，为(right - 1) - (left + 1) + 1 =  right -left - 1
			start = left + 1;
			maxlen = right - left - 1;
		}
	}
	string longestPalindrome(string s) {
		int start = 0, maxlen = 0;
		for (int i = 0; i < s.size(); ++i) {
			help(s, i, i, start, maxlen);
			help(s, i, i + 1, start, maxlen);
		}
		return s.substr(start, maxlen);
	}
};
