/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:01:05
 * @link    github.com/taseikyo
 */

char str[] = "1234";
int size = sizeof(str) / sizeof(char);

bool IsSwap(int from, int to) {
	bool bCan = true;
	for (int i = from; i < to; i++) {
		if (str[to] == str[i]) {
			bCan = false;
			break;
		}
	}
	return bCan;
}

void Permutation(int from, int to) {
	if (from == to) {
		for (int i = 0; i <= to; i++) {
			cout << str[i];
		}
		cout << '\n';
		return;
	}

	for (int i = from; i <= to; i++) {
		if (!IsSwap(from, i)) {
			continue;
		}
		swap(str[i], str[from]);
		Permutation(from + 1, to);
		swap(str[i], str[from]);
	}
}