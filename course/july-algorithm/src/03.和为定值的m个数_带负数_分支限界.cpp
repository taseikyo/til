/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-30 17:06:33
 * @link    github.com/taseikyo
 */

int a[] = {1, 2, 3, 4, 5};
int size = sizeof(a) / sizeof(int);
int sum = 10;

// x[] 为最终解，i 为考察第 x[i] 加入，has 表示当前和
void FindNUmber(bool *x, int i, int has, int negative,
                int positive) {
	if (i >= size) {
		return;
	}
	if (has + a[i] == sum) {
		x[i] = true;
		Print(x);
		x[i] = false;
	}
	if (a[i] >= 0) {
		if (has + positive >= sum && has + a[i] <= sum) {
			x[i] = true;
			FindNUmber(x, i + 1, has + a[i], negative, positive - a[i]);
		}
		if (has + positive - a[i] >= sum) {
			x[i] = false;
			FindNUmber(x, i + 1, has, negative, positive - a[i]);
		}

	} else {
		if (has + a[i] + positive >= sum) {
			x[i] = true;
			FindNUmber(x, i + 1, has + a[i], negative - a[i], positive);
		}
		if (has + negative <= sum && has + positive >= sum) {
			x[i] = false;
			FindNUmber(x, i + 1, has + a[i], negative - a[i], positive);
		}
	}

}


int main(int argc, char const *argv[]) {
	int positive, negative;
	Sum(a, size, negative, positive);
	bool *x = new bool[size];
	memset(x, 0, size);
	FindNUmber(x, 0, 0, negative, positive);
	delete[] x;
	return 0;
}