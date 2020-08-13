/**
 * @date    2020-08-13 10:11:34
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * （1）leetcode 与 leetkode。
 * 那么我们需要找到 'c' 和 'k'，然后比较 'ode' 和 'ode' 是否相同。
 * （2）leetcode 与 leetode。
 * 我们发现 'c' 和 'o' 不相同，然后比较 'ode' 和 'ode' 是否相同。
 */

class Solution {
  public:
	bool oneEditAway(string first, string second) {
		const int len1 = first.size();
		const int len2 = second.size();
		if (abs(len1 - len2) > 1) {
			return false;
		}
		// 保证第一个长
		if (len2 > len1) return oneEditAway(second, first);
		for (int i = 0; i < len2; ++i) {
			if (first[i] != second[i]) {
				if (len1 == len2) {
					// 如果相等，比较后面
					return first.substr(i + 1) == second.substr(i + 1);
				} else {
					// 不相等，first 后一位开始，second 当前开始
					return first.substr(i + 1) == second.substr(i);
				}
			}
		}
		return true;
	}
};