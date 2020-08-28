/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-13 16:15:05
 * @link    github.com/taseikyo
 */

// 最简单的就是直接暴力循环，另一种就是二分，找到每行的第一个负数
class Solution {
  public:
	int countNegatives(vector<vector<int>>& grid) {
		int ans = 0;
		for (const vector<int>& row : grid)
			ans += upper_bound(row.rbegin(), row.rend(), -1) - row.rbegin();
		return ans;
	}

	// 这个方法很有趣，从右上开始
	// 由于从上往下是递减的，所以不需要每次重置 c
	int countNegatives1(vector<vector<int>>& grid) {
		int m(grid.size()), n(grid[0].size()), r(0), c(n - 1);
		while (r < m) {
			while (c >= 0 && grid[r][c] < 0) c--;
			ans += n - c - 1;
			r++;
		}
		return ans;
	}
};

