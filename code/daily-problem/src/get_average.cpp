/**
 * @date    2020-09-09 16:03:16
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

#include <iostream>
#include <vector>

using namespace std;

int get_average(vector<int> a) {
	int n = a.size();
	int aver = 0;
	int rest = 0;  // [0, n)
	for (int i = 0; i < n; ++i) {
		aver += a[i] / n;
		int temp = a[i] % n;
		if (temp < 0) {
			temp += n;
			aver -= 1;
		}
		// rest + temp > n，防止溢出
		if (rest > n - temp) {
			aver++;
			rest -= (n - temp);
		} else {
			rest += temp;
		}
	}
	// 假定负数结果向0取整
	return (aver >= 0) ? aver : aver + 1;
}

int main(int argc, char* argv[]) {
	vector<int> v{ -1, -10, 4, 56, 12};
	// 12
	cout << get_average(v) <<endl;
	return 0;
}