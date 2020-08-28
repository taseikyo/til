/**
 * @date    2020-08-22 18:27:32
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") {
			return "0";
		}
		int n1 = num1.size();
		int n2 = num2.size();
		int carry = 0;
		vector<int> ans(n1 + n2, 0);
		for (int i = n1 - 1; i >= 0; --i) {
			for (int j = n2 - 1; j >= 0; --j) {
				ans[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
			}
		}
		for (int i = ans.size() - 1; i >= 0; --i) {
			ans[i] += carry;
			carry = ans[i] / 10;
			ans[i] %= 10;
		}
		carry = 0;
		for (auto c : ans) {
			if (c != 0) {
				break;
			}
			++carry;
		}
		string ret(ans.size()-carry, '0');
		for (int i = carry; i < ans.size(); ++i) {
			ret[i-carry] += ans[i];
		}
		return ret;
	}
};