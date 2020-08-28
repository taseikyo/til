/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 20:45:35
 * @link    github.com/taseikyo
 */

// 令人头大，没有思路
// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/

class Solution {
  public:
	int NumberOf1Between1AndN_Solution(int n) {
		int cnt = 0;
		for (int m = 1; m <= n; m *= 10) {
			int a = n / m, b = n % m;
			cnt += (a + 8) / 10 * m + (a % 10 == 1 ? b + 1 : 0);
		}
		return cnt;
	}
};