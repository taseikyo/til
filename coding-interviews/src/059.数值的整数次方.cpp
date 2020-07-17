/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:27:59
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	double Power(double base, int exponent) {
		if (base == 0) {
			return 0;
		}
		if (exponent == 0) {
			return 1;
		}
		if (exponent < 0) {
			return 1 / Power(base, -exponent);
		}
		if (exponent % 2 == 0) {
			return Power(base, exponent / 2) * Power(base, exponent / 2);
		}
		return Power(base, exponent / 2) * Power(base, exponent / 2) * base;
	}
};