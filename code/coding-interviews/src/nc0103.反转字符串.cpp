/**
 * @date    2020-09-03 19:26:58
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * 反转字符串
	 * @param str string字符串
	 * @return string字符串
	 */
	string solve(string str) {
		int l = 0, r = str.size() - 1;
		while (l < r) {
			swap(str[l++], str[r--]);
		}
		return str;
	}
};