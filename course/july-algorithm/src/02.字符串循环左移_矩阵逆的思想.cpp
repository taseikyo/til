/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 15:51:36
 * @link    github.com/taseikyo
 */

void ReverseString(char*s, int from, int to) {
	while (from < to) {
		char t = s[from];
		s[from++] = s[to];
		s[to--] = t;
	}
}

void LeftRotatestring(char*s, int n, int m) {
	m %= n;
	Reversestring(s, 0, m - 1);
	ReverseString(s, m, n - 1);
	ReverseString(s, 0, n - 1);
}