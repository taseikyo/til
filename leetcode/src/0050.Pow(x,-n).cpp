/**
 * @date    2020-08-26 20:30:46
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	double myPow(double x, int n) {
		if (x == 1.0) return x;
		if (n < -1) return 1 / (myPow(x, -(n + 1)) * x);
		if (n == -1) return 1 / x;
		if (n == 0) return 1;
		if (n == 1) return x;
		double ret = myPow(x, n / 2);
		if (n % 2 == 0)
			return ret * ret;
		else
			return ret * ret * x;
	}
};

// -1.00000
// -2147483648
// 会溢出
class Solution {
  public:
	double myPow(double x, int n) {
		if (n == 0) {
			return 1;
		} else if (n == 1) {
			return x;
		} else if (n < 0) {
			if (n == INT_MIN) {
				return 1.0 / myPow(x, INT_MAX);
			}
			return 1.0 / myPow(x, -n);
		} else if (n == 2) {
			return x * x;
		}
		double ans = myPow(x, n / 2);
		if (n & 1) {
			return x * ans * ans;
		}
		return  ans * ans;
	}
};