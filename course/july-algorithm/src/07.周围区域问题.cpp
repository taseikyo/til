/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-02 17:40:20
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	void solve(vector<vector<char>>& board) {
		if (board. empty()) return;
		const int m = board.size();
		const int n = board[0].size();
		for (int i = 0; i < n; i++) {
			bfs(board, 0, i);
			bfs(board, m - 1, i);
		}
		for (int j = 1; j < m - 1; j++) {
			bfs(board, j, 0);
			bfs(board, j, n - 1);
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				if (board[i][j] == '0')
					board[i][j] = 'x';
				else if (board[i][j] == '+')
					board[i][j] = '0';
			}
	}
};

void bfs(vector<vector<char>>& board, int i, int j) {
	typedef pair<int, int> state_t;
	queue<state_t> q;
	const int m = board.size();
	const int n = board[0].size();
	state_t start = {i, j};
	if (is_valid(start)) {
		board[i][j] = '+';
		q.push(start);
	}
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		auto new_states = state_extend(cur);
		for (auto s : new_states) {
			q.push(s);
		}
	}
}

auto is_valid(const state_t &s) {
	const int x = s.first;
	const int y = s.second;

	if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != '0') {
		return false;
	}
	return true;
}

auto state_extend = [&](const state_t &s) {
	vector<state_t> result;
	const int x = s.first;
	const int y = s.second;
	// 上下左右
	const state_t new_states[4] = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
	for (int i = 0; i < 4; ++i) {
		if (is_valid(new_states[i])) {
			board[new_states[i].first][new_states[i].second] = '+';
			result.push_back(new_states[i]);
		}
	}
}