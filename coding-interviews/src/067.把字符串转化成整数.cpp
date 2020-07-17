/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 13:38:23
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int StrToInt(string str) {
		if (str.empty()) {
			return 0;
		}
		if (str.size() == 1) {
			if (str[0] >= '0' && str[0] <= '9') {
				return str[0] - '0';
			}
			return 0;
		}
		int sign = 1;
		int ans = 0;
		int i = 0;
		if (str[0] == '+' || str[0] == '-') {
			sign = str[0] == '-' ? -1 : 1;
			++i;
		}
		while (i < str.size()) {
			if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
			        && str[i] <= 'z')) {
				return 0;
			}
			if (str[i] == '+' || str[i] == '-') {
				return 0;
			}
			if (str[i] == '.') {
				break;
			}
			if (str[i] >= '0' && str[i] <= '9') {
				ans = ans * 10 + str[i] - '0';
			} else {
				return 0;
			}
			++i;
		}
		return sign * ans;
	}
};