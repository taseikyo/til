/**
 * @date    2020-08-13 09:58:53
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	bool CheckPermutation(string s1, string s2) {
		if (s1.size() != s2.size()) {
			return false;
		}
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());
		return s1 == s2;
	}
};