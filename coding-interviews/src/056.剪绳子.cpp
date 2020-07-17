/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 23:22:35
 * @link    github.com/taseikyo
 */

// 递归
// 第一刀在 i 处，剩下 n-i
// f(n) = max(f(i)*f(n-i))
class Solution {
  public:
	int cutRope(int n) {
		if (n < 2) {
			return 0;
		} else if (n == 2) {
			return 1;
		} else if (n == 3) {
			return 2;
		}
		return foo(n);
	}
	int foo(int n) {
		if (n < 4) {
			return n;
		}
		int ans = 0;
		for (int i = 1; i < n / 2 + 1; ++i) {
			ans = max(foo(i) * cutRope(n - 1), ans);
		}
		return ans;
	}
};

// 动态规划
class Solution {
  public:
	int cutRope(int n) {
		if (n == 2) {
			return 1;
		} else if (n == 3) {
			return 2;
		}

		vector<int> f(n + 1, -1);
		for (int i = 1; i <= 4; ++i) {
			f[i] = i;
		}
		for (int i = 5; i <= n; ++i) {
			for (int j = 1; j < i / 2 + 1; ++j) {
				f[i] = max(f[i], j * f[i - j]);
			}
		}
		return f[n];
	}
};