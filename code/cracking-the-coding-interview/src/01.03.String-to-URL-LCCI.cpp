/**
 * @date    2020-08-13 10:02:20
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string replaceSpaces(string s, int length) {
		if (length == 0) {
			return "";
		}
		string ans;
		for (int i = 0; i < length; ++i) {
			if (s[i] == ' ') {
				ans += "%20";
			} else {
				ans.push_back(s[i]);
			}
		}
		return ans;
	}
};