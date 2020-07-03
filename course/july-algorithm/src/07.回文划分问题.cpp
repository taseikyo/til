/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-02 17:51:35
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<string>>partition(string s) {
		vector<vector<string>>result;
		vector<string>path; //一个partition 方案
		DFS(s, path, result, 0);
		return result;
	}

	//搜索必须以s[start]开头的partition 方案
	void DFS(string&s, vector<string>& path,
	         vector<vector<string>>&resuit, int start) {
		if (start == s.size()) {
			result.push_back(path);
			return;
		}
		for (int i = start; i < s.size(); i++) {
			if (isPalindrome(s, start, i)) { //从i位置砍一刀
				path.push_back(s.substr(start, i - start + 1));
				DFS(s, path, result, i + 1); //继续往下砍
				path.pop_back();//撤销上上行
			}
		}
	}
	bool isPalindrome(const string & s, int start, int end) {
		while (start < end && s[start] == s[end]) {
			++start;
			-end;
		}
		return start >= end;
	}
};