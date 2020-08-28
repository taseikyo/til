/**
 * @date    2020-08-23 18:40:15
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	// 上下左右 左上右上右下左下
	int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1};
	int dy[8] = {0, 0, -1, 1, -1, 1, 1, -1};
	void gameOfLife(vector<vector<int>>& board) {
		// -1 下一轮活；-2 下一轮死亡
		int m = board.size();
		int n = board[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int cnt = checkAlive(board, i, j);
				if (board[i][j] == 1) {
					if (cnt < 2 || cnt > 3) {
						board[i][j] = -2;
					}
				} else {
					if (cnt == 3) {
						board[i][j] = -1;
					}
				}
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == -2) {
					board[i][j] = 0;
				} else if (board[i][j] == -1) {
					board[i][j] = 1;
				}
			}
		}
	}

	int checkAlive(vector<vector<int>>& board, int x, int y) {
		int m = board.size();
		int n = board[0].size();
		int cnt = 0;
		for (int i = 0; i < 8; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
				continue;
			}
			if (board[nx][ny] == 1 || board[nx][ny] == -2) {
				++cnt;
			}
		}
		return cnt;
	}
};