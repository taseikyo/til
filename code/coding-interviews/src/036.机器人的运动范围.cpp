/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 15:25:47
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/6e5207314b5241fb83f2329e89fdecc8?tpId=13&&tqId=11219&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
 */

class Solution {

  public:
	using V = vector<int>;
	using VV = vector<V>;
	int dir[5] = { -1, 0, 1, 0, -1};

	int check(int n) {
		int sum = 0;

		while (n) {
			sum += (n % 10);
			n /= 10;
		}

		return sum;
	}

	void dfs(int x, int y, int threshold, int r, int c, int &ret, VV &mark) {
		// 检查下标 和 是否访问
		if (x < 0 || x >= r || y < 0 || y >= c || mark[x][y] == 1) {
			return;
		}
		// 检查当前坐标是否满足条件
		if (check(x) + check(y) > threshold) {
			return;
		}
		// 代码走到这里，说明当前坐标符合条件
		mark[x][y] = 1;
		ret += 1;

		for (int i = 0; i < 4; ++i) {
			dfs(x + dir[i], y + dir[i + 1], threshold, r, c, ret, mark);
		}

	}
	int movingCount(int threshold, int rows, int cols) {
		if (threshold <= 0) {
			return 0;
		}

		VV mark(rows, V(cols, -1));
		int ret = 0;
		dfs(0, 0, threshold, rows, cols, ret, mark);
		return ret;
	}
};