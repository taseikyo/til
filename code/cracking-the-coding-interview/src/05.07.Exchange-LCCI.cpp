/**
 * @date    2020-08-23 17:11:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int exchangeBits(int num) {
		return ((num & 0x55555555) << 1) | ((num & 0xaaaaaaaa) >> 1);
	}
};