/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-29 19:26:03
 * @link    github.com/taseikyo
 */

// https://leetcode-cn.com/problems/shortest-palindrome/solution/kmpsuan-fa-zhu-shi-xiang-xi-by-li-zhi-chao-4/
class Solution {
  public:
	string shortestPalindrome(string s) {

		string rs = s;
		reverse(rs.begin(), rs.end());
		//用 s 做模版去匹配 rs
		vector<int> next (s.size(), 0);
		getNext(s, next);
		int p = 0;//执行模版开头
		for (int i = 0; i < rs.size(); i++) {
			while ( rs[i] != s[p] && p > 0) {
				p = next[p];
			}
			if ( rs[i] == s[p]) {
				p++;
			}
		}
		string endfix = "";
		if ( p < s.size() )
			endfix =  s.substr(p);
		return rs + endfix;

	}
	void getNext(const string &pattern, vector<int> &next) {
		if ( next.size() <= 2) return;
		//已匹配长度为 0 或者 1 时，最长前后缀长度 为 0
		next[0] = 0;
		next[1] = 0;
		int index =
		    0;// 模版中已经匹配的长度，即下一个要匹配的元素下标
		int maxPrefixlen =
		    0;// 已匹配模版的最长前后缀长度，即最长前后缀下一个元素下标
		for ( index = 2; index < pattern.size(); index++) {
			while ( pattern[maxPrefixlen] != pattern[index - 1]
			        && maxPrefixlen > 0) {
				maxPrefixlen = next[maxPrefixlen];//回退
			}
			//新增的已匹配元素下标是 index-1
			if ( pattern[maxPrefixlen] == pattern[index - 1] ) {
				maxPrefixlen++;//已匹配长度加1
			}
			next[index] = maxPrefixlen;

		}
	}
};

// 119/120，最后一个测试用例是 4w 个 a，中间是 cd
class Solution {
  public:
	string shortestPalindrome(string s) {
		for (int i = 0; i < s.size(); ++i) {
			string tmp = string(s.rbegin(), s.rbegin() + i) + s;
			if (check(tmp)) {
				return tmp;
			}
		}
		return "";
	}
	bool check(string& s) {
		int i = 0, j = s.size() - 1;
		while (i <= j) {
			if (s[i++] != s[j--]) {
				return false;
			}
		}
		return true;
	}
};