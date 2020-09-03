/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:07:38
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param s string字符串
	 * @return bool布尔型
	 */
	bool isValid(string s) {
		if (s.empty()) {
			return true;
		}
		if (s.size() == 1) {
			return false;
		}
		stack<char> stk;
		for (auto c : s) {
			if (stk.size() && (c - stk.top() == 1 || c - stk.top() == 2)) {
				stk.pop();
			} else {
				stk.push(c);
			}
		}
		return stk.empty();
	}
};