/**
 * @date    2020-08-23 18:36:39
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 每生成一个 ( 就需要一个 )
// 最后左右括号个数为 0 时就说明生成完了
class Solution {
  public:
	vector<string> ans;
	vector<string> generateParenthesis(int n) {
		help(n, 0, "");
		return ans;
	}
	void help(int left, int right, string tmp) {
		if (left == 0 && right == 0) {
			ans.push_back(tmp);
			return;
		}
		if (left > 0) {
			help(left - 1, right + 1, tmp + "(");
		}
		if (right > 0) {
			help(left, right - 1, tmp + ")");
		}
	}
};