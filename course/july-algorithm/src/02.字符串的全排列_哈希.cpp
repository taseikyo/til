/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:05:48
 * @link    github.com/taseikyo
 */

#define MARK_SIZE 256

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
	int mark[MARK_SIZE];
	for (int i = 0; i < MARK_SIZE; ++i) {
		mark[i] = 0;
	}
	for (int i = from; i <= to; i++) {
		if (mark[str[i]] == 1) {
			continue;
		}
		mark[str[i]]  = 1;
		swap(str[i], str[from]);
		Permutation(from + 1, to);
		swap(str[i], str[from]);
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	Permutation(0, size - 2);
	return 0;
}