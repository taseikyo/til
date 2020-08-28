/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 23:07:50
 * @link    github.com/taseikyo
 */

// f(n) = f(0) + f(1) + f(2) + ... f(n-1)
// f(n-1) = f(0) + f(1) + f(2) + ... f(n-2)
// => f(n) = 2*f(n-1)
class Solution {
  public:
	int jumpFloorII(int n) {
		if (n <= 0) {
			return -1;
		} else if (n == 1) {
			return 1;
		}
		return 2 * jumpFloorII(n - 1);
	}
};