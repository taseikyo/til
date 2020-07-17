/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 13:21:56
 * @link    github.com/taseikyo
 */
// 递归
// https://www.nowcoder.com/questionTerminal/45327ae22b7b413ea21df13ee7d6429c?answerType=1&f=discussion
class Solution {
  public:
	bool match(char* s, char* p) {
		// 如果 s 和 p 同时为空
		if (*s == '\0' && *p == '\0') return true;
		// 如果 s不为空， 但是 p 为空
		if (*p == '\0') return false;
		// 如果没有 '*'
		if (*(p + 1) != '*') {
			if (*s != '\0' && (*s == *p || *p == '.'))
				return match(s + 1, p + 1);
			else
				return false;
		}
		// 如果有 '*'
		else {
			bool ret = false;
			// 重复 1 次或多次
			if (*s != '\0' && (*s == *p || *p == '.'))
				ret = match(s + 1, p);
			// 重复 0 次
			return ret || match(s, p + 2);
		}
	}
};
// 动态规划
// f[i][j]表示s的前i个和p的前j个能否匹配
class Solution {
  public:
	bool match(char* s, char* p) {
		int sn = strlen(s), pn = strlen(p);
		vector<vector<char>> f(sn + 1, vector<char>(pn + 1, 0));
		for (int i = 0; i <= sn; ++i) {
			for (int j = 0; j <= pn; ++j) {
				// 初始条件
				if (j == 0) f[i][j] = (i == 0);
				else {
					// 如果没有 '*'
					if (p[j - 1] != '*') {
						if (i >= 1 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
							f[i][j] = f[i - 1][j - 1];
						}
					}
					// 如果有 '*'
					else {
						// 重复 0 次
						if (j >= 2) {
							f[i][j] |= f[i][j - 2];
						}
						// 重复 1 次或者多次
						// 这里要用 | 连接， 不然重复 0 次的会直接覆盖
						if (i >= 1 && j >= 2 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
							f[i][j] |= f[i - 1][j];
						}
					}
				}

			}
		}
		return f[sn][pn];
	}
};
