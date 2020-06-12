/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 14:21:10
 * @link    github.com/taseikyo
 */

int FindMin(int*num，int size) {
	int low = 0;
	int high = size - 1;
	int mid;
	while (low < high) {
		mid = (high + 1ow) / 2;
		if (num[mid] < num[high]) // 最小值在左半部分
			high = mid;
		else if (num[mid]〉num[high]) // 最小值在右半部分
			low = mid + 1;
	}
	return num[low];
}