/**
 * @date    2020-09-05 16:55:18
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 第一次提交没考虑 "ABBB" 2
// 第二次超时
class Solution {
  public:
	int characterReplacement(string s, int k) {
		int n = s.size();
		if (n < 2 || n <= k) {
			return n;
		}
		int count = 0, ans = 0;
		for (int i = 0; i < n; ++i) {
			while (i > 0 && i < n && s[i] == s[i - 1]) ++i;
			int j = i + 1;
			count = 0;
			for (; j < n; ++j) {
				if (s[i] != s[j]) {
					count++;
					if (count > k) break;
				}
			}
			ans = max(ans, j - i);
			if (count <= k && i > 0) {
				// "ABBB"
				ans = max(ans, (j - i + min(k - count, i)));
			}
		}
		return ans;
	}
};

// 没看懂
class Solution {
  public:
	int characterReplacement(string s, int k) {
		int n = s.length();
		int ans = 0, left = 0, maxCnt = 0;
		vector<int> letter(26, 0);
		for (int i = 0; i < s.length(); i++) {
			letter[s[i] - 'A']++;
			maxCnt = max(maxCnt, letter[s[i] - 'A']);
			if (i - left + 1 - maxCnt > k) {
				letter[s[left] - 'A']--;
				left++;
			}
			ans = max(ans, i - left + 1);
		}
		return ans;
	}
};