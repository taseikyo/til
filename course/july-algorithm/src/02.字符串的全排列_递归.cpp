/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 15:55:38
 * @link    github.com/taseikyo
 */

char str[] = "1234";
int size = sizeof(str) / sizeof(char);

void Permutation(int from, int to) {
	if (from == to) {
		for (int i = 0; i <= to; i++) {
			cout << str[i];
		}
		cout << '\n';
		return;
	}
	for (int i = from; i <= to; i++) {
		swap(str[i], str[from]);
		Permutation(from + 1, to);
		swap(str[i], str[from]);
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	Permutation(0, size - 2);
	return 0;
}