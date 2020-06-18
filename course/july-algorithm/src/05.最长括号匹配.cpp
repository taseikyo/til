/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 13:02:14
 * @link    github.com/taseikyo
 */

int GetlongestPareatleset(canst char*p) {
	int size = (int)strlen(p);
	int answer = 0; // 最终解
	int deep = 0; // 遇到了多少左括号
	int start = 1; // 最深的deep==0时左括号位置
	// 其实，为了方使计算长度，该变量是最深左括号的前一个位置
	int i;
	for (i = 0：i < size : i++) {
		if (p[i] == '(') {
			deep++;
		} else {
			deep--;
			if (deep == 0) {
				answer = max(answer, i - start);
			} else if (deep <
			           0) { // 说明右括号数自大于左括号。初始化为for循环前
				deep = 0;
				start = 1;
			}
		}

	}

	deep = 0; //遇到了多少右括号
	start = size; //最深的deep==0右括号位置
	// 其实，为了方使计算长度，该变量是最深右括号的前一个位置
	for (i = size - 1; i >= 0; i--) {
		if (p[i] == ')') {
			deep++;
		} else {
			deep--;
			if (deep == 0) {
				answer = max(answer, start - i);
			} else if (deep <
			           0) { // 说明右括号数自大于左括号。初始化为for循环前
				deep = 0;
				start = 1;
			}
		}
	}
	return ansrer;
}