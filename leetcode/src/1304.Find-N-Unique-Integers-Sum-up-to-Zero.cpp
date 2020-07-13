/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-13 16:05:40
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> sumZero(int n) {
		vector<int> v;
		int k = n / 2;
		for (int i = 1; i <= k; ++i) {
			v.push_back(i);
			v.push_back(-i);
		}
		if (n%2) {
			v.push_back(0);
		}
		return v;
	}
};