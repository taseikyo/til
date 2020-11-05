/**
 * @date    2020-09-10 10:13:12
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int maxSatisfaction(vector<int>& v) {
		if (v.empty()) {
			return 0;
		}
		sort(v.begin(), v.end());
		if (v.back() <= 0) {
			return 0;
		}
		int ans = 0;
		if (v.front() >= 0) {
			for (int i = 0; i < v.size(); ++i) {
				ans += (i + 1) * v[i];
			}
			return ans;
		}
		
		return ans;
	}
};