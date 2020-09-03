/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:37:11
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * 二分查找
	 * @param n int整型 数组长度
	 * @param v int整型 查找值
	 * @param a int整型vector 有序数组
	 * @return int整型
	 */
	int upper_bound_(int n, int v, vector<int>& a) {
		// 弱智参数，vector 传 n 干嘛
		int l = 0, r = n - 1;
		while (l <= r) {
			int m = l + (r - l) / 2;
			if (a[m] >= v) {
				r = m - 1;
			} else {
				l = m + 1;
			}
		}
		return (l < n && a[l] >= v) ? (l + 1) : (n + 1);
	}
};