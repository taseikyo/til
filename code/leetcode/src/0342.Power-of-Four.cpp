/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 23:09:28
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool isPowerOfFour(int n) {
		if (n <= 0) {
			return false;
		}
		// 是 4 的幂肯定是 2 的幂
		// 2 的幂中 1 在奇数位上的是 4 的幂
		// 与 0x55555555 按位与，如果在奇数位上有数则不为 0
		if (!(n & (n - 1))) {
			return (n & 0x55555555);
		}
		return false;// 0101
	}
};

// 讨论区有个解法，前提你的知道下面这个
// (4^n - 1) % 3 == 0
bool isPowerOfFour(int num) {
    return num > 0 && (num & (num - 1)) == 0 && (num - 1) % 3 == 0;
}