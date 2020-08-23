/**
 * @date    2020-08-23 19:22:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	void rotate(vector<vector<int>>& matrix) {
		// 左上-右下对折
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < i; j++)
				swap(matrix[i][j], matrix[j][i]);

		// 中间对折
		for (auto& row : matrix)
			reverse(row.begin(), row.end());
	}
};