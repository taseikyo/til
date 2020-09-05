/**
 * @date    2020-09-01 09:05:59
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string decodeString(string s) {
		int i = 0;
		return decodeString(s, i);
	}
	string decodeString(string& s, int& i) {
		string res;
		while (i < s.size() && s[i] != ']') {
			if (s[i] < '0' || s[i] > '9') {
				res += s[i++];
			} else {
				int count = 0;
				while (s[i] >= '0' && s[i] <= '9') {
					count = count * 10 + s[i++] - '0';
				}
				++i;
				string tmp = decodeString(s, i);
				++i;
				while (count--) {
					res += tmp;
				}
			}
		}
		return res;
	}
};