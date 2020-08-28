/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-06 22:00:09
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/12d959b108cb42b1ab72cef4d36af5ec?tpId=13&&tqId=11196&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 *
 * 汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！
 */

class Solution {
  public:
	string LeftRotateString(string str, int n) {
		if (str.empty()) {
			return str;
		}
		if (n >= str.size()) {
			n %= str.size();
		}
		if (n == 0) {
			return str;
		}
		// BA = (A'B')'
		reverse(str.begin(), str.begin() + n);
		reverse(str.begin() + n, str.end());
		reverse(str.begin(), str.end());
		return str;
	}
};

// 从讨论区扣的，tql
class Solution {
  public:
	string LeftRotateString(string str, int n) {
		int len = str.length();
		if (len == 0) return "";
		n = n % len;
		str += str;
		return str.substr(n, len);
	}
};