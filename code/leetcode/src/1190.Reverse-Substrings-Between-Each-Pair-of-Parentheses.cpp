/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 14:05:14
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	string reverseParentheses(string s) {
		string ret;
		stack<int> st;
		// 交换
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(') {
				st.push(i + 1);
			} else if (s[i] == ')') {
				reverse(s.begin() + st.top(), s.begin() + 1);
				s.pop();
			}
		}
		// 赋值
		for (auto c : s) {
			if (c != '(' && c != ')') {
				ret.push_back(c);
			}
		}
		return ret;
	}
};