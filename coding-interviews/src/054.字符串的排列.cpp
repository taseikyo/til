/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 22:41:11
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<string> Permutation(string str) {
		int n = str.size();
		if (n == 0) {
			return {};
		} else if (n == 1) {
			return {str};
		}
		vector<string> v;
		foo(str, v, 0);
		sort(v.begin(), v.end());
		return v;
	}
    
	void foo(string str, vector<string> &v, int s) {
		if (s == str.size() - 1) {
			v.push_back(str);
			return;
		}
		for (int i = s; i < str.size(); ++i) {
			bool cnt = false;
			for (int j = s; j < i; ++j) {
				if (str[i] == str[j]) {
					cnt = true;
					break;
				}
			}
			if (cnt) {
				continue;
			}
			swap(str[s], str[i]);
			foo(str, v, s + 1);
			swap(str[s], str[i]);
		}
	}
};