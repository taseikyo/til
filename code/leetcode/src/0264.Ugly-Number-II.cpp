/**
 * @date    2020-08-27 20:51:11
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int nthUglyNumber(int n) {
		if (n <= 0) {
			return 0;
		}
		int p2 = 0, p3 = 0, p5 = 0;
		vector<int> v(n);
		v[0] = 1;
		for (int i = 1; i < n; i++) {
			v[i] = min(v[p2] * 2, min(v[p3] * 3, v[p5] * 5));
			if (v[i] == v[p2] * 2) p2++;
			if (v[i] == v[p3] * 3) p3++;
			if (v[i] == v[p5] * 5) p5++;
		}
		return v[n - 1];
	}
};