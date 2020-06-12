/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 14:00:09
 * @link    github.com/taseikyo
 */

double MaxAddSub(double *a, int from, int to) {
	if (to == from)
		return a[from];
	int middle = (from + to) / 2;
	double m1 = MaxAddSub(a, from, middle);
	double m2 = MaxAddSub(a, middle + 1, to);
	int i, left = a[middle], now = a[middle];
	for (i = middle - 1; i >= from; --i) {
		now += a[i];
		left = max(now, left);
	}
	int right = a[middle + 1];
	now = a[middle + 1];
	for (i = middle + 2; i <= to; ++i) {
		now += a[i];
		right = max(now, right);
	}
	double m3 = left + right;
	return std::max(m1, m2, m3);
}
