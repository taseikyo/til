/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-29 20:18:58
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int lengthOfLastWord(string s) {
		int ans = 0, j = s.size() - 1;
		while (j >= 0 && s[j] == ' ') --j;
		while (j >= 0 && s[j--] != ' ') ++ans;
		return ans;
	}
};