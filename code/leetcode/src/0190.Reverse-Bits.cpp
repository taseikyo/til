/**
 * @date    2020-08-28 20:26:05
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t ans = 0;
		//进制的本质
		int i = 32;
		while (i--) {
			ans <<= 1;
			ans += n & 1;
			n >>= 1;
		}
		return ans;
	}
};