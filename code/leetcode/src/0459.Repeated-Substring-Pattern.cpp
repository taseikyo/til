/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-24 20:45:27
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool repeatedSubstringPattern(string s) {
		int n = s.size();
		for (int i = 1; i <= n / 2; ++i) {
			auto ret = check(s, i, i);
			if (ret) {
				return true;
			}
		}
		return false;
	}

	bool check(string& s, int cur, int size) {
		int n = s.size();
		if (cur + size > n) {
			return false;
		}
		for (int i = 0; i < size; ++i) {
			if (s[i] != s[cur + i]) {
				return false;
			}
		}
		if (cur + size == n) {
			return true;
		}
		return check(s, cur + size, size);
	}
};

class Solution {
  public:
	bool repeatedSubstringPattern(string s) {
		return (s + s).find(s, 1) != s.size();
	}
};