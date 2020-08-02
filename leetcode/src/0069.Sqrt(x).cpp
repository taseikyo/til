/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:07:16
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int mySqrt(int x) {
		if (x <= 1) {
			return x;
		}
		int l = 1, h = x;
		while (l <= h) {
			int mid = l + (h - l) / 2;
			int sqrt = x / mid;
			if (sqrt == mid) {
				return mid;
			} else if (mid > sqrt) {
				h = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		return h;
	}
};