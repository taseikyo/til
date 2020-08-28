/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-09 22:37:48
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	string removeDuplicates(string S) {
		string a;
		for (auto& c : S) {
			if (a.size() && a.back() == c) a.pop_back();
			else a.push_back(c);
		}
		return a;
	}
};