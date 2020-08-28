/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 13:12:06
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool isValid(string s) {
		if (s.empty()) {
			return true;
		}
		if (s.size() == 1) {
			return false;
		}
		stack<char> stk;
		// ASCII 中 () 相邻
		// [] {} 中间隔了一个
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