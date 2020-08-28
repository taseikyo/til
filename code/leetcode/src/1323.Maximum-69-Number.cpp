/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-31 22:12:21
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int maximum69Number (int num) {
		vector<int> v;
		while (num) {
			v.push_back(num % 10);
			num /= 10;
		}
		for (auto it = v.rbegin(); it != v.rend(); ++it) {
			if (*it == 6) {
				*it = 9;
				break;
			}
		}
		int ans = 0;
		for (auto it = v.rbegin(); it != v.rend(); ++it) {
			ans = 10 * ans + *it;
		}
		return ans;
	}
};

class Solution {
  public:
	int maximum69Number (int num) {
		string n = to_string(num);
		for (auto& c : n) {
			if ((int) (c - '0') == 6) {
				c = '9';
				break;
			}
		}
		return stoi(n);
	}
};