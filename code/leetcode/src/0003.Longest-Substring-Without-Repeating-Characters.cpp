/**
 * @date    2020-08-20 16:32:04
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() < 2) {
			return s.size();
		}
		int n = s.size(), i = 0, j = 0;
		unordered_set<int> set;
		int ans = 0;
		while (i < n && j < n) {
			if (set.find(s[j]) == set.end()) {
				ans = max(ans, j - i + 1);
				set.insert(s[j++]);
			} else {
				set.erase(s[i++]);
			}
		}
		return ans;
	}
};