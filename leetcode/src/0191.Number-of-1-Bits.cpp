/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:37:44
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int hammingWeight(uint32_t n) {
		int x = 0;
		while (n) {
			if (n & 1) {
				++x;
			}
			n >>= 1;
		}
		return x;
	}
};