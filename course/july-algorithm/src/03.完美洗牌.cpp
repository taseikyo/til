/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-30 17:31:54
 * @link    github.com/taseikyo
 */

void PerfectShuffle2(int *a, int n) {
	int n2, m, i, k, t;
	for (; n > 1;) {
		//step 1
		n2 = n * 2;
		for (k = 0, m = 1; n2 / m >= 3; ++k, m *= 3)
			;
		m /= 2;
		// 2m = 3^k-1, 3k <= 2n < 3^(k+1)
		// step 2
		right_rotate(a + m, m, n);
		// step3
		for (i = 0, t = 1; i < k; ++i, t *= 3) {
			cycle_leader(a, t, m * 2 + 1);
		}
		// step4
		a += m * 2;
		n -= m;
	}
	//n=1
	t = a[1];
	a[1] = a[2];
	a[2] = t;
}