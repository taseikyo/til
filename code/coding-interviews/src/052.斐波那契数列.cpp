/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 22:11:55
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int Fibonacci(int n) {
		int a = 0, b = 1;
		if (n < 2) {
			return n;
		}
		for (int i = 2; i <= n; ++i) {
			int tmp = a + b;
			a = b;
			b = tmp;
		}
		return b;
	}
};