/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 22:10:11
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int jumpFloor(int n) {
		if (n <= 2) {
			return n;
		}
		return jumpFloor(n - 1) + jumpFloor(n - 2);
	}
};