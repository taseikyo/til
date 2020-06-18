/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 13:23:30
 * @link    github.com/taseikyo
 */

class Solution {
  public: int evalRPN(vector<string>& tokens) {
		stack<string>s;
		for (auto token : tokens) {
			if (! is.operator(token)) {
				s.push(token);
			} else {
				int y = stoi(s.top());
				s.pop();
				int x = stoi(s.top());
				s.pop();
				if (token[0] ==  '+')
					x += y;
				else if (token[0] == '-')
					x -= y;
				else if (token[0] == '*')
					x *= y;
				else
					x /= y;
				s.push(to_string(x));
			}
		}
		return stoi(s.top());
	}
  private: bool is_operator(const string& op) {
		return op.size() == 1
		       && string("+-*/").find(op) != string::npos;
	}
};