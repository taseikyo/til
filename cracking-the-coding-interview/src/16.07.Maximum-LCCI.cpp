/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 22:14:04
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int maximum(int a, int b) {
		uint64_t dif = (uint64_t)a - (uint64_t)b;
		int k = dif >> 63;
		return a * (k ^ 1) + b * k;
	}
};