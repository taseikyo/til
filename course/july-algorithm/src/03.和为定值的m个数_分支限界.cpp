/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-30 16:59:14
 * @link    github.com/taseikyo
 */

int a[] = {1, 2, 3, 4, 5};
int size = sizeof(a) / sizeof(int);
int sum = 10;

// x[] 为最终解，i 为考察第 x[i] 加入，has 表示当前和
// residue 表示剩余部分的和
void FindNUmber(bool *x, int i, int has, int residue) {
	if (i >= size) {
		return;
	}
	if (has + a[i] == sum) {
		x[i] = true;
		Print(x);
		x[i] = false;
	} else if (has + residue >= sum && has + a[i] <= sum) {
		x[i] = true;
		FindNUmber(x, i + 1, has + a[i], residue - a[i]);
	}
	if (has + residue - a[i] >= sum) {
		x[i] = false;
		FindNUmber(x, i + 1, has, residue - a[i]);
	}
}


int main(int argc, char const *argv[]) {
	int residue = Sum(a, size);
	bool *x = new bool[size];
	memset(x, 0, size);
	FindNUmber(x, 0, 0, residue);
	delete[] x;
	return 0;
}