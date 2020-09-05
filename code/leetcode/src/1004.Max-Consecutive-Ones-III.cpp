/**
 * @date    2020-09-05 16:04:04
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int longestOnes(vector<int>& v, int k) {
		int n = v.size();
		if (n <= k) return n;
		int l = 0, r = 0, count = k, ans = 0;
		while (r < n) {
			if (v[r] == 0) {
				if (count-- == 0) {
					ans = max(ans, r - l);
					while (l < r && v[l] != 0) ++l;
					++l;
					++count;
				}
			}
			++r;
		}
		return ans > (r - l) ? ans : r - l;
	}
};