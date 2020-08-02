/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:07:24
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	string reverseVowels(string s) {
		vector<char> v = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
		if (s.empty()) {
			return s;
		}
		int i = 0, j = s.size() - 1;
		while (i < j) {
			while ((i < j)
			        && (find(v.begin(), v.end(), s[i]) == v.end())) ++i;
			while ((i < j)
			        && (find(v.begin(), v.end(), s[j]) == v.end())) --j;
			swap(s[i], s[j]);
			++i, --j;
		}
		return s;
	}
};