/**
 * @date    2020-08-13 11:42:40
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 最简单的做法，保存含 0 的行和列，最后把这些行和列都置为 0
class Solution {
  public:
	void setZeroes(vector<vector<int>>& m) {
		set<int> row, col;
		int rows = m.size();
		int cols = m[0].size();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (m[i][j] == 0) {
					row.insert(i);
					col.insert(j);
				}
			}
		}
		for (auto it = row.begin(); it != row.end(); ++it) {
			for (int i = 0; i < cols; ++i) {
				m[*it][i] = 0;
			}
		}
		for (auto it = col.begin(); it != col.end(); ++it) {
			for (int i = 0; i < rows; ++i) {
				m[i][*it] = 0;
			}
		}
	}
};

// 一个巧妙做法，用第一行第一列作为标记
// 然后再用另外变量记录第一行第一列
class Solution {
  public:
	void setZeroes(vector<vector<int>>& m) {
		bool col = false, row = false;
		int rows = m.size();
		int cols = m[0].size();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (m[i][j] == 0) {
					m[0][j] = 0;
					m[i][0] = 0;
					if (i == 0) {
						row = true;
					}
					if (j == 0) {
						col = true;
					}
				}
			}
		}
		for (int i = 1; i < cols; ++i) {
			if (m[0][i] == 0) {
				for (int j = 1; j < rows; ++j) {
					m[j][i] = 0;
				}
			}
		}
		for (int i = 1; i < rows; ++i) {
			if (m[i][0] == 0) {
				for (int j = 1; j < cols; ++j) {
					m[i][j] = 0;
				}
			}
		}
		if (row) {
			for (int i = 0; i < cols; ++i) {
				m[0][i] = 0;
			}
		}
		if (col) {
			for (int i = 0; i < rows; ++i) {
				m[i][0] = 0;
			}
		}
	}
};