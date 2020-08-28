/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 13:16:57
 * @link    github.com/taseikyo
 */

// https://www.nowcoder.com/questionTerminal/c61c6999eecb4b8f88a98f66b273a3cc?answerType=1&f=discussion

class Solution {
  public:
	char *mat = 0;
	int h = 0, w = 0;
	int str_len = 0;
	int dir[5] = { -1, 0, 1, 0, -1};

	bool dfs(int i, int j, int pos, char *str) {
		// 边界检查，
		if (i < 0 || i >= h || j < 0 || j >= w) {
			return false;
		}

		char ch = mat[i * w + j];
		// 判断是否访问过
		// 如果没有访问过，判断是否和字符串str[pos]匹配
		if (ch == '#' || ch != str[pos]) {
			return false;
		}

		// 如果匹配，判断是否匹配到最后一个字符
		if (pos + 1  == str_len) {
			return true;
		}

		// 说明当前字符成功匹配，标记一下，下次不能再次进入
		mat[i * w + j] = '#';
		for (int k = 0; k < 4; ++k) {
			if (dfs(i + dir[k], j + dir[k + 1], pos + 1, str)) {
				return true;
			}
		}
		// 如果4个方向都无法匹配 str[pos + 1]
		// 则回溯， 将'#' 还原成 ch
		mat[i * w + j] = ch;
		// 说明此次匹配是不成功的
		return false;
	}

	bool hasPath(char* matrix, int rows, int cols, char* str) {
		mat = matrix;
		h = rows, w = cols;
		str_len = strlen(str);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (dfs(i, j, 0, str)) {
					return true;
				}
			}
		}
		return false;
	}
};