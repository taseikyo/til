/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-06 22:14:58
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&&tqId=11155&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
 */

// 这个题感觉挺傻逼的，要求没说明白
// 看了题解也贼弱智，真就直接在 str 后面写啊
//
// 开始我是想着计算空格个数，然后分配新内存，最后返回，然而函数返回 void，str 也是个一级指针
class Solution {
  public:
	void replaceSpace(char *str, int length) {
		if (str == nullptr || length <= 0)
			return;
		int cnt = 0;  // 空格的个数
		for (int i = 0; i != length; ++i) {
			if (str[i] == ' ') ++cnt;
		}
		if (!cnt) return; // 没有空格，直接返回
		int new_length = length + cnt * 2;
		for (int i = length; i >= 0; --i) {
			if (str[i] == ' ') {
				str[new_length--] = '0';
				str[new_length--] = '2';
				str[new_length--] = '%';
			} else {
				str[new_length--] = str[i];
			}
		}
	}
};