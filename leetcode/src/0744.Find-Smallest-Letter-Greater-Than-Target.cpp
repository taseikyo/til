/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:09:06
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	char nextGreatestLetter(vector<char>& letters, char target) {
		int n = letters.size();
		int l = 0, h = n - 1;
		while (l <= h) {
			int m = l + (h - l) / 2;
			if (letters[m] <= target) {
				l = m + 1;
			} else {
				h = m - 1;
			}
		}
		return l < n ? letters[l] : letters[0];
	}
};