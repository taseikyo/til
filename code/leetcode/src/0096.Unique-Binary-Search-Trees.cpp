/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 15:18:13
 * @link    github.com/taseikyo
 */


// https://leetcode.com/problems/unique-binary-search-trees/discuss/31666/DP-Solution-in-6-lines-with-explanation.-F(i-n)-G(i-1)-*-G(n-i)
// g(n) 为所求的 bst 数量
// f(i, n) 表示 i 为根节点的 bst 数量
// 显然，g(n) = f(1, n) + f(2, n) + ... f(n, n), g(0) = g(1) = 1
// 而 f(i, n) = g(i-1)*g(n-i)，这个公式也好理解，就是 i 为根的数量为左子树 * 右子树
// 太强了，虽然知道用 dp，然而递推公式难搞
class Solution {
  public:
	int numTrees(int n) {
		vector<int> v(n + 1);
		v[0] = v[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {
				v[i] += v[j - 1] * v[i - j];
			}
		}
		return v[n];
	}
};