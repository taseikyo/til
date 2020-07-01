/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 23:33:07
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> plusOne(vector<int>& digits) {
		int carry = 1;
		for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
			if (carry == 0) {
				break;
			}
			*it += carry;
			carry = *it / 10;
			*it %= 10;
		}
		if (carry) {
			digits.insert(digits.begin(), carry);
		}
		return digits;
	}
};