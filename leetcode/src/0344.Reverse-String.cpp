/**
 * @date    2020-08-21 17:11:22
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	void reverseString(vector<char>& s) {
		int i = 0, j = s.size() - 1;
		while(i < j) {
			swap(s[i++], s[j--]);
		}
	}
};