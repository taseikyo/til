/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-31 22:18:36
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int mul = 1, sum = 0;
	int subtractProductAndSum(int n) {
		while (n) {
			mul *= n % 10;
			sum += n % 10;
			n /= 10;
		}
		return mul - sum;
	}
};