/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 22:27:24
 * @link    github.com/taseikyo
 */

// f[n] = f[n-1] + f[n-2]
class Solution {
  public:
	int rectCover(int n) {
		if (n == 0 || n == 1 || n == 2) return n;
		int a = 1, b = 2, c;
		for (int i = 3; i <= n; ++i) {
			c = a + b;
			a = b;
			b = c;
		}
		return b;
	}
};