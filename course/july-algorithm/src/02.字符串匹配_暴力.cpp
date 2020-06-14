/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:21:54
 * @link    github.com/taseikyo
 */

int BruteForceSearch(const char*s，const char*p) {
	int i = 0; // 当前匹配到的原始串首位
	int j = 0; // 模式串的匹配位置
	int size = (int)strlen(s);
	int psize = (int)strlen(p);
	while ((i < size) && (j < psize)) {
		if (s[i + j] == p[j]) {
			//若匹配，则模式串匹配位置后移
			j++;
		} else {
			// 不匹配，则比对下一个位置，模式串回溯到首位
			i++;
			j = 0;
		}
	}
	if (j >= psize)
		return i;
	return -1;
}