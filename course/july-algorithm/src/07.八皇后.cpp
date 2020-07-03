/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-02 17:57:47
 * @link    github.com/taseikyo
 */

#include<iostream>
#include<stdlib.h>

using namespace std;

int x[8], tot = 0;

bool B(int x[], int k) {
	int i;
	for (i = 0; i < k; i++)
		if (x[i] == x[k] || (abs(x[i] - x[k]) == abs(i - k)))
			return 0;
	return 1;
}

int queen(int i) {
	if (i >= 8) {
		tot++;
		for (i = 0; i < 8; i++)
			cout << x[i] << " ";
		cout << endl;
		return 0;
	}
	for (int k = 0; k < 8; k++) {
		x[i] = k;
		if (B(x, i))
			queen(i + 1);
	}
}

int main() {
	queen(0);
	cout << tot << endl;
	return 0;
}