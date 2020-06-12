/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 15:45:20
 * @link    github.com/taseikyo
 */
#include <iostream>
using namespace std;
#define len(a) (sizeof(a)/sizeof(a[0])) // 数组长度

int lis(int arr[], int len) {
	int longest[len];
	for (int i = 0; i < len; i++ ) {
		longest[i] = 1;
	}
	for (int j = 1; j < len; j++) {
		for (int i = 0; i < j; i++ ) {
			// 注意longest[j]<longest[i]-1这个条件, 不能省略
			if (arr[j] > arr[i] && longest[j] < longest[i] - 1) {
				// 计算以arr[j]结尾的序列的最长递增子序列长度
				longest[j] = longest[i] + 1;
			}
		}
	}
	int max = 0;
	for (int j = 0; j < len; j++) {
		cout << "longest[" << j << "]=" << longest[j] << endl;
		if (longest[j] > max)
			//从longest[]中找出最大值
			max = longest[j];
	}
	return max;
}