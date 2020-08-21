/**
 * @date    2020-08-19 17:43:44
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		backtrack(res, n, 0, "");
		return res;
	}

	//回溯：left表示可使用的做左括号数'(',right表示可使用的右括号数')'
	void backtrack(vector<string>& res, int left, int right,
	               string track) {
		if (!right && !left) res.push_back(track);
		else {
			/*使用一个左括号，同时可使用右括号数加1，这样可避免生成无效括号*/
			if (left > 0) backtrack(res, left - 1, right + 1,
				                        track + '(');
			/*可使用的右括号数大于0，则用来补齐原来的左括号*/
			if (right > 0) backtrack(res, left, right - 1, track + ')');
		}
	}
};