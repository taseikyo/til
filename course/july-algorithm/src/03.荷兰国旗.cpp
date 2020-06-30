/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-30 17:13:40
 * @link    github.com/taseikyo
 */

void Holland(int*a, int length) {
	int begin = 0;
	int current = 0;
	int end = length - 1;
	while (current <= end) {
		if (a[current] == 2) {
			swap(a[end], a[current]);
			end--;
		} else if (a[current] == 1) {
			current++;
		} else { //if(a[current=0])
			if (begin == current) {
				begin++;
				current++;
			} else {
				swap(a[current], a[begin]);
				begin++;
			}
		}
	}
}