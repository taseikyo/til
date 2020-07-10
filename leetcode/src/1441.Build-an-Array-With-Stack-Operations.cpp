/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-09 18:04:52
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<string> buildArray(vector<int>& target, int n) {
		vector<string> v;
		int size = target.size();
		int i = 0;
		int j = 1;
		while (i < size && j <= n) {
			if (target[i] == j) {
				v.push_back("Push");
				++i;
			} else {
				v.push_back("Push");
				v.push_back("Pop");
			}
			++j;
		}
		return v;
	}
};