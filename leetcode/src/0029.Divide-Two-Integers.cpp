/**
 * @date    2020-08-26 19:53:38
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// https://leetcode-cn.com/problems/divide-two-integers/solution/er-fen-fa-di-gui-qiu-jie-chu-li-te-shu-zhi-by-cgli/

// 用被除数不断地减去除数效率太低，不满足时间要求。因此可以采用二分法。
// 1. 被除数a, 除数b；
// 2. 被除数a减去1xb，若结果大于等于被除数的一半，则减去2xb，假设a减去nxb后小于a的一半；
// 3. 令被除数a=a-nxb，继续执行步骤2，直到a<b。

class Solution {
  public:
	int div(int a, int b) {
		if (a < b) return 0;
		int ans = 1;
		int acc = b;
		while (a - acc >= acc) {
			ans += ans;
			acc += acc;
		}
		return ans + div(a - acc, b);
	}

	int divide(int dividend, int divisor) {
		if (dividend == 0) return 0;
		else if (divisor == 1) return dividend;
		else if (divisor == -1) return (dividend == INT_MIN) ?
			                               INT_MAX : -dividend;

		int a = dividend;
		int b = divisor;
		int ans = 0;
		bool flag = (a > 0 && b > 0 || a < 0
		             && b < 0); //同符号时为真

		if (b == INT_MIN) { //处理b为特殊值的情况
			return (a == INT_MIN) ? 1 : 0;
		}
		if (a == INT_MIN) { //处理a为特殊值的情况
			a = (flag) ? a - b : a + b;
			++ans;
		}
		a = (a > 0) ? a : -a;
		b = (b > 0) ? b : -b;
		ans += div(a, b);
		if (!flag) ans = -ans;
		return ans;
	}
};