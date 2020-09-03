/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:14:49
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param x int整型
	 * @return int整型
	 */
	int sqrt(int x) {
		if (x <= 1)
			return x;

		int begin = 1;
		int end = x;
		int middle = 0;
		while (begin <= end) {
			middle = (begin + end) / 2;
			// 不要写成 middle*middle==x，会溢出
			if (middle == x / middle) {
				return middle;
			} else {
				if (middle < x / middle) {
					begin = middle + 1;
				} else {
					end = middle - 1;
				}
			}

		}
		// 结束条件 end 一定 < begin，所以返回 end
		return end;
	}
};