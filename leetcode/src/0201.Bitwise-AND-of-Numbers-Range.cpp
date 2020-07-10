/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:54:45
 * @link    github.com/taseikyo
 */

// 会超时
class Solution {
  public:
	int rangeBitwiseAnd(int m, int n) {
		int x = m;
		for (int i = m + 1; i <= n; ++i) {
			x &= i;
		}
		return x;
	}
};

// 评论区的代码，不是很懂
// Consider the bits from low to high
// if n > m, the lowest bit will be 0,
// and then we could transfer the problem to sub-problem:
// rangeBitwiseAnd(m>>1, n>>1)
class Solution {
  public:
	int rangeBitwiseAnd(int m, int n) {
		return (n > m) ? (rangeBitwiseAnd(m / 2, n / 2) << 1) : m;
	}
};

class Solution {
  public:
	int rangeBitwiseAnd(int m, int n) {
		int count = 0;
		while (m != n) {
			m >>= 1;
			n >>= 1;
			count++;
		}
		return m << count;
	}
};