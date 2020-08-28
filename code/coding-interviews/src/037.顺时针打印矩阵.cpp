/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 15:36:01
 * @link    github.com/taseikyo
 */

// https://www.nowcoder.com/practice/9b4c81a02cd34f76be2659fa0d54342a?tpId=13&&tqId=11172&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking


// 由外而内打印矩阵，以左上角和右下角坐标定义一个矩阵
// 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字
// 例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
// 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
// 
// 对于给出的例子输出顺序为
// 1. 上 1 2 3 4
// 2. 右 8 12 16
// 3. 下 15 14 13
// 4. 左 9 5
// 下和左可能有特殊情况（一行、一列需要注意下）
class Solution {
  public:
	void print(int lx, int ly, int rx, int ry,
	           vector<vector<int>> &matrix, vector<int> &ret) {
		for (int j = ly; j <= ry; ++j) ret.push_back(matrix[lx][j]);
		for (int i = lx + 1; i <= rx; ++i) ret.push_back(matrix[i][ry]);
		int h = rx - lx + 1;
		if (h > 1)
			for (int rj = ry - 1; rj >= ly; --rj) ret.push_back(matrix[rx][rj]);
		int w = ry - ly + 1;
		if (w > 1)
			for (int ri = rx - 1; ri >= lx + 1;
			        --ri) ret.push_back(matrix[ri][ly]);
	}
	vector<int> printMatrix(vector<vector<int>>& matrix) {
		vector<int> ret;
		if (matrix.empty()) return ret;
		int lx = 0, ly = 0;
		int rx = matrix.size() - 1, ry = matrix[0].size() - 1;
		while (lx <= rx && ly <= ry) {
			print(lx++, ly++, rx--, ry--, matrix, ret);
		}
		return ret;
	}

};