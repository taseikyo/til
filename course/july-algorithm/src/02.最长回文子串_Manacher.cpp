/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 17:01:30
 * @link    github.com/taseikyo
 */

void Manacher(char*s, int*P) {
	int size = strlen(s);
	P[0] = 1;
	int id = 0;
	int mx = 1;
	for (int i = 1; i < size; i++) {
		if (mx > i) {
			P[i] = min(P[2 * id - i], mx - i);
		} else {
			P[i] = 1;
		}
		for (; s[i + P[i]] == s[i - P[i]]; P[i]++);
		if (mx < i + P[i]) {
			mx = i + P[i];
			id = i;
		}
	}
}
