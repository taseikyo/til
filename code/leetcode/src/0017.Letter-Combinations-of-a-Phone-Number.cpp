/**
 * @date    2020-08-26 09:13:04
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */



class Solution {
  public:
	unordered_map<char, string> table{
		{'0', " "}, {'1', "*"}, {'2', "abc"},
		{'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
		{'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"},
		{'9', "wxyz"}};
	vector<string> ans;
	vector<string> letterCombinations(string digits) {
		if (digits.empty()) {
			return ans;
		}
		string tmp;
		backtrace(digits, tmp, 0);
		return ans;
	}
	void backtrace(string& digits, string& tmp, int cur) {
		if (tmp.size() == digits.size()) {
			ans.push_back(tmp);
			return;
		}
		for (auto c : table[digits[cur]]) {
			tmp.push_back(c);
			backtrace(digits, tmp, cur + 1);
			tmp.pop_back();

		}
	}
};