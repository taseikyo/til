/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:33:28
 * @link    github.com/taseikyo
 */

void CalcNext(char*p，int next[]) {
	int nLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < nLen - 1) {
		// 此刻，k即next[j-1]，且p[k]表示前缀，p[j]表示后缀
		// 注：k==-1表示未找到k前缀与k后缀相等，首次分析可先忽略
		if (k == -1 || p[j] == p[k]) {
			++k; ++j; next[j] = k;
		} else {
			// p[j]与p[k]失配，则继续递归前缀索引p[next[k]]
			k = next[k];
		}
	}
}

int KMP(int n) {
	int ans = -1; int i = 0; int j = 0;
	int pattern_len = strlen(g_pattern);
	while (i < n) {
		if (j == -1 || gs[i] == g_pattern[j]) {
			++i; ++j;
		} else {
			j = g_next[j];
		}
		if (j == pattern_len) {
			ans = i - pattern_len;
			break;
		}
	}
	return ans;
}