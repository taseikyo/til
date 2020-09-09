/**
 * @date    2020-09-09 20:21:57
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 讨论区
// 分治法，将字符串分成三部分
// 前半部分是包含若干大于 k 次的字符串
// 中间是零星的不超过 k 次的字符串
// 剩下就是后半部分
// 
// 最后返回前半部分和后半部分符合要求字符串
class Solution {
  public:
	int longestSubstring(string s, int k) {
		if (k <= 1) return s.size();
		if (s.empty() || s.size() < k) return 0;

		vector<int> hash(128, 0);
		for (char c : s) ++hash[c];

		int i = 0;
		while (i < s.size() && hash[s[i]] >= k) ++i;
		if (i == s.size()) return s.size();

		int l = longestSubstring(s.substr(0, i), k);
		while (i < s.size() && hash[s[i]] < k) ++i;
		int r = longestSubstring(s.substr(i), k);

		return max(l, r);
	}
};