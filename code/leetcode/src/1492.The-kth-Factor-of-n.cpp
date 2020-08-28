/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-31 22:40:54
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int kthFactor(int n, int k) {
		vector<int> v;
		for (int i = 1; i <= n; ++i) {
			if (n % i == 0) {
				v.push_back(i);
			}
		}
		if (k > v.size()) {
			return -1;
		}
		return v[k - 1];
	}
};