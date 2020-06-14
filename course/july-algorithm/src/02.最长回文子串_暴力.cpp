/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:46:22
 * @link    github.com/taseikyo
 */

int LongestPalindrome(const char *s, int n) {
	int i, j, max;
	if (s = 0 || n < 1)
		return 0;
	max = 0;
	// i is the middle point of the palindrome
	for (i = 0, i < n; ++i) {
		for (j = 0, (i - j >= 0) && (i + j < n), ++j) {
			// if the length of the palindrome is odd.
			if (s[i - j] != s[i + j])
				break
			}
		if (j * 2 + 1 > max)
			max = j * 2 + 1;
		for (j = 0, (i - j >= 0) && (i + j + 1 < n), ++j) {
			//for the even case
			if (s[i - j] != s[i + j + 1])
				break;
		}
		if (j * 2 + 2 > max)
			max = j * 2 + 2;
	}
	return max;
}
