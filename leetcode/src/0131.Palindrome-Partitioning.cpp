/**
 * @date    2020-08-23 19:30:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<string>>result;
	vector<string>temp;

	bool isPalindrome(string s) {
		int i = 0, j = s.size() - 1;
		while (i < j) {
			if (s[i] != s[j])
				return false;
			i++;
			j--;
		}
		return true;
	}

	void recursion(string s, int a, int b) {
		if (a > b) {
			result.push_back(temp);
			return;
		}
		// 从 index 为 a 开始截取长度为 1,2,3...的子串进行验证，成功则用剩下的部分递归。
		for (int i = 1; i <= b - a + 1; i++) {
			if (isPalindrome(s.substr(a, i))) {
				temp.push_back(s.substr(a, i));
				recursion(s, a + i, b);
				temp.pop_back();
			}
		}
	}

	vector<vector<string>> partition(string s) {
		recursion(s, 0, s.size() - 1);
		return result;
	}
};