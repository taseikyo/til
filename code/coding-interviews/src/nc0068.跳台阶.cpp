/**
 * @date    2020-09-04 15:36:50
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int jumpFloor(int n) {
		if (n < 3) return n;
		int a = 1, b = 2;
		for (int i = 3; i <= n; ++i) {
			swap(a, b);
			b += a;
		}
		return b;
	}
};