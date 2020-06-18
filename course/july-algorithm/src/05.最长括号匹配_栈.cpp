/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 12:53:25
 * @link    github.com/taseikyo
 */

class Solution {
  public: int longeatValidParenthesea(string s) {
		int max_len = 0, last = -1; // the position of the last')
		stack<int> lefts; // keep track of the positions of non-matching'('s
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(') {
				lefts.push(i);
			} else {
				if (lefts.empty()) {
					// no matching left
					last = i;
				} else {
					// find a natching pair
					lefts.pop();
					if (lefts.empty()) {
						max_len = max(max_len, i - last);
					} else {
						max_len = max(max_len, i - lefts.top());
					}
				}
				return max_len;
			}
		}
	}
};