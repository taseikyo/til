/**
 * @date    2020-08-23 16:44:37
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int myAtoi(string str) {
		if (str.empty()) {
			return 0;
		}
		// negative -> 1
		int sign = 0;
		long long ans = 0;
		int i = 0;
		// remove leading space
		while (str[i] == ' ') {
			++i;
		}
		// sign
		if (str[i] == '-' || str[i] == '+') {
			sign = str[i] == '-' ? 1 : 0;
			++i;
		}
		// like "word 1232"
		if (i == 0 && !(str[i] >= '0' && str[i] <= '9')) {
			return 0;
		}
		for (; i < str.size(); ++i) {
			// "123 w"
			if (i > 0 && !(str[i] >= '0' && str[i] <= '9')) {
				break;
			}
			ans = ans * 10 + str[i] - '0';
			if (sign && -ans < INT_MIN) {
				return INT_MIN;
			}
			if (!sign && ans > INT_MAX) {
				return INT_MAX;
			}
		}
		return sign ? -ans : ans;
	}
};