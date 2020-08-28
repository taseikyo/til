/**
 * @date    2020-08-13 10:09:45
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */


class Solution {
  public:
	bool canPermutePalindrome(string s) {
		bitset<128> flags;
		for (auto ch : s) {
			flags.flip(ch);
		}
		return flags.count() < 2; //出现奇数次的字符少于2个
	}
};
