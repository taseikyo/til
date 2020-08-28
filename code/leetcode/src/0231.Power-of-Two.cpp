/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:40:40
 * @link    github.com/taseikyo
 */
// 如果一个数是 2 的幂，则只有最高位的 1
// n&(n-1) 会去掉最后一个 1
class Solution {
  public:
	bool isPowerOfTwo(int n) {
		if (n <= 0) return false;
		return !(n & (n - 1));
	}
};