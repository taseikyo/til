/**
 * @date    2020-08-13 09:54:38
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	bool isUnique(string astr) {
		if (astr.size() < 2) {
			return true;
		}
		sort(astr.begin(), astr.end());
		for (int i = 1; i < astr.size(); ++i) {
			if (astr[i] == astr[i - 1]) {
				return false;
			}
		}
		return true;
	}
};