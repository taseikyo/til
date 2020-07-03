/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 16:20:45
 * @link    github.com/taseikyo
 */

// p[0...n]存储了n+1个数,其中,(p[i-1], p[i])是矩阵 i 的阶;
// s[i][j] 记录 A[i...j]从什么位置断开;m[i][j] 记录数乘最小值
void MatrixMultiply(int*p, int n, int**m, int**s) {
	int r, i, j, k, t;
	for (i = 1; i <= n; i++)
		m[i][i] = 0;
	// r 个连续矩阵的连乘:上面的初始化,相当于r=1
	for (r = 2; r <= n; r++) {
		for (i = 1; i <= n - r + 1; i++) {
			j = i + r - 1;
			// 初始化 m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];
			// m[i][i] = 0 所以这里直接省了
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (k = i + 1; k < j; k++) {
				t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}