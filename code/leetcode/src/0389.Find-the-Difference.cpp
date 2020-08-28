/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 23:23:03
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	char findTheDifference(string s, string t) {
		char c = 0;
		for (auto i : s) {
			c ^= i;
		}
		for (auto i : t) {
			c ^= i;
		}
		return c;
	}
};