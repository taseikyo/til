/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-06 22:25:22
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/1c82e8cf713b4bbeb2a5b31cf5b0417c?tpId=13&&tqId=11187&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.（从0开始计数）
 */

class Solution {
  public:
	int FirstNotRepeatingChar(string str) {
		if (str.length() == 0) {
			return -1;
		} else if (str.length() == 1) {
			return 0;
		}
		// A-Z对应的ASCII码为65-90，a-z对应的ASCII码值为97-122
		int map[58] = {0};
		for (auto c : str) {
			map[c - 65] += 1;
		}
		for (int i = 0; i < str.length(); ++i) {
			if (map[str[i] - 65] == 1) {
				return i;
			}
		}
		return -1;
	}
};