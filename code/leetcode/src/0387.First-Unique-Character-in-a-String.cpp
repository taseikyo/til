/**
 * @date    2020-09-09 20:10:14
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int firstUniqChar(string s) {
		unordered_map<char, int> table;
		for (auto c : s) {
			table[c]++;
		}
		for (int i = 0; i < s.size(); ++i) {
			if (table[s[i]] == 1) {
				return i;
			}
		}
		return -1;
	}
};