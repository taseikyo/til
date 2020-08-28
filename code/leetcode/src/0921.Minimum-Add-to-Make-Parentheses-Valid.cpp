/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-09 17:59:30
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int minAddToMakeValid(string S) {
		stack<char> stk;
		for (auto c : S) {
			if (c == ')') {
				if (stk.size() && stk.top() == '(') {
					stk.pop();
					continue;
				}
			}
			stk.push(c);
		}
		return stk.size();
	}
};