/**
 * @date    2020-08-28 20:57:34
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// a ^ b是无进位的相加； a&b得到每一位的进位
class Solution {
  public:
	int getSum(int a, int b) {
		int sum, carry = 0;
		sum = a ^ b;
		carry = ((unsigned int)a & b) << 1;
		if (carry) {
			return getSum(sum, carry);
		}
		return sum;
	}
};