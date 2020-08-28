/**
 * @date    2020-08-20 15:41:12
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int n, m;
	int dx[8] = { -1, 1, 0, 0, -1, 1, -1, 1}, dy[8] = {0, 0, -1, 1, -1, -1, 1, 1};

	void dfs(vector<vector<char>>& board, int r, int c) {
		char tmp = board[r][c]; // 保存元字符
		board[r][c] = '#'; // 标志访问
		int cntM = 0; // 四邻炸弹计数器
		for (int i = 0; i < 8; ++i) { // 首先探炸弹
			int x = r + dx[i];
			int y = c + dy[i];
			bool notEdge = x >= 0 && x < n && y >= 0 && y < m;
			if (notEdge && board[x][y] == 'M') {
				cntM++;
			}
		}
		if (!cntM) { // 如果四周没炸弹，递归向下继续dfs
			board[r][c] = 'B';
			for (int i = 0; i < 8; ++i) { // 再递归探四周的'E'
				int x = r + dx[i];
				int y = c + dy[i];
				bool notEdge = x >= 0 && x < n && y >= 0 && y < m;
				if (notEdge && board[x][y] == 'E') {
					dfs(board, x, y);
				}
			}
		} else { // 否则修改后直接返回
			board[r][c] = '0' + cntM;
		}
	}

	vector<vector<char>> updateBoard(vector<vector<char>>& board,
	vector<int>& click) {
		n = board.size(); m = board[0].size();
		if (board[click[0]][click[1]] == 'M') {
			board[click[0]][click[1]] = 'X';
		} else {
			dfs(board, click[0], click[1]);
		}

		return board;
	}
};