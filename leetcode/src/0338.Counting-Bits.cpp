/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-15 23:38:11
 * @link    github.com/taseikyo
 */

// 这个方法就很巧妙
// 对于最后一位是 1 的，比如 01010101，那么它 1 的个数就是 0101010 + 1
class Solution {
  public:
	vector<int> countBits(int num) {
		vector<int> v(num + 1);
		for (int i = 0; i <= num; ++i) {
			v[i] = (i & 1) ? (v[i >> 1] + 1) : v[i >> 1];
		}
		return v;
	}
};