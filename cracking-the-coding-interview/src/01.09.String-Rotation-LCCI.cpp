/**
 * @date    2020-08-13 16:06:33
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 对于 AB 和 BA，将一个字符串自身相加
// 比如 ABAB 那么它将包含 BA，然后查找即可
class Solution {
  public:
	bool isFlipedString(string s1, string s2) {
		return s1.size() == s2.size()
		       && (s2 + s2).find(s1) != string::npos;
	}
};