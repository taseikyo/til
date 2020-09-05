/**
 * @date    2020-09-05 19:29:20
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int maxVowels(string s, int k) {
		unordered_set<char> map{'a', 'e', 'i', 'o', 'u'};
		int ans = 0, cnt = 0, l = 0, r = 0;
		while (r < s.size()) {
			if (map.find(s[r++]) != map.end()) {
				++cnt;
			}
			if (r - l == k) {
				ans = max(ans, cnt);
				if (map.find(s[l--]) != map.end()) {
					--cnt;
				}
			}
		}
		return ans;
	}
};


// nb
class Solution {
  public:
	int maxVowels(string s, int k) {
		int cnt = 0;
		int begin = 0;
		int end = 0;
		for (; end < k; ++end) {
			cnt += isVowel(s[end]);
		}
		int mx = cnt;
		for (; end < s.size(); ++begin, ++end) {
			cnt -= isVowel(s[begin]);
			cnt += isVowel(s[end]);
			mx = max(mx, cnt);
		}
		return mx;
	}

	inline int isVowel(char c) {
		return (c == 'a' || c == 'e' || c == 'i' || c == 'o'
		        || c == 'u') ? 1 : 0;
	}
};