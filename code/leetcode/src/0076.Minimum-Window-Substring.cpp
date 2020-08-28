/**
 * @date    2020-08-20 16:42:39
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string minWindow(string s, string t) {
		int left = 0, right = 0, start = 0, minLen = INT_MAX;
		unordered_map<char, int> need;
		unordered_map<char, int> window;
		for (char c : t) {
			need[c]++; // 目标字符数
		}
		int match = 0;
		while (right < s.size()) { // 滑窗开始
			char c1 = s[right];
			if (need.count(c1)) { // 当前字符为目标字符
				window[c1]++; // 更新窗口内字符数
				if (window[c1] ==
				        need[c1]) { // 若改字符的窗口内字符数 = 需要的目标字符数，匹配字符数加一
					match++;
				}
			}
			right++; // 窗口右扩
			while (match ==
			        need.size()) { // 当窗口内的所有字符均已匹配完成，开始窗口左侧缩窗
				if (right - left <
				        minLen) { // 更新当前窗口最小值及窗口起始位置
					minLen = right - left;
					start = left;
				}
				char c2 = s[left];
				if (need.count(c2)) { // 若左侧字符为目标字符
					window[c2]--; // 更新窗口内字符统计
					if (window[c2] <
					        need[c2]) { // 窗口变更后不满足目标字符数要求，匹配字符数减一，循环结束，重新开始新一轮右扩
						match--;
					}
				}
				left++; // 窗口左缩
			}
		}
		return minLen == INT_MAX ? "" : s.substr(start, minLen);
	}
};