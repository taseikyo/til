/**
 * @date    2020-09-04 16:23:56
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param s string字符串
	 * @return int整型
	 */
	int longestValidParentheses(string s) {
		stack<int> stk;
		int start = -1, ans = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(') {
				stk.push(i);
			} else {
				if (stk.empty()) {
					start = i;
				} else {
					stk.pop();
					if (stk.empty()) {
						ans = max(ans, i - start);
					} else {
						ans = max(ans, i - stk.top());
					}
				}
			}
		}
		return ans;
	}
};