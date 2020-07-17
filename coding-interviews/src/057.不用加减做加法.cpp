/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:20:38
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int Add(int num1, int num2) {
		int sum, carry;
		do {
			// 将两个数异或，模拟加法中相加不进位的结果
			sum = num1 ^ num2;
			// 只考虑进位的情况
			carry = (num1 & num2) << 1;
			num1 = sum;
			num2 = carry;
		} while (num2 != 0);
		// 将结果相加的过程就重复上述过程，直到进位为0
		return sum;
	}
};