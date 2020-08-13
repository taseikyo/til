/**
 * @date    2020-08-13 11:28:06
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 1. 沿 右上-左下 对角线折叠
// 2. 上下对折
class Solution {
  public:
	void rotate(vector<vector<int>>& matrix) {
		int count = matrix.size();
		if (count < 2) {
			return;
		}
		// 1.
		for (int i = 0; i < count; ++i) {
			for (int j = 0; j < count - i - 1; ++j) {
				swap(matrix[i][j], matrix[count - 1 - j][count - 1 - i])
			}
		}
		// 2.
		for (int i = 0; i < count/2; ++i) {
			for (int j = 0; j < count; ++j) {
				swap(matrix[i][j], matrix[count-1-i][j])
			}
		}
	}
};