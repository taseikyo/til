/**
 * @date    2020-08-21 15:20:39
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int compress(vector<char>& chars) {
		int len = 0;
		for (int i = 0, cnt = 1; i < chars.size(); i++, cnt++) {
			if (i + 1 == chars.size() || chars[i] != chars[i + 1]) {
				chars[len++] = chars[i];
				if (cnt > 1) {
					for (char ch : to_string(cnt)) {
						chars[len++] = ch;
					}
				}
				cnt = 0;
			}
		}
		return len;
	}
};