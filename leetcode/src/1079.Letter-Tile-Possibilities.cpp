/**
 * @date    2020-08-27 19:12:57
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int ans = 0;
	int numTilePossibilities(string tiles) {
		if (tiles.size() == 0) {
			return 0;
		}
		vector<int> visit(tiles.size(), 0);
		sort(tiles.begin(), tiles.end());
		backtrace(tiles, visit);
		return ans;
	}
	void backtrace(string& tiles, vector<int>& visit) {
		for (int i = 0; i < tiles.size(); i++) {
			if ((i > 0) && (tiles[i] == tiles[i - 1]
			                && (visit[i - 1] == 0)))
				continue;
			if (visit[i] == 0) {
				visit[i] = 1;
				ans++;
				backtrace(tiles, visit);
				visit[i] = 0;
			}
		}
	}
};

class Solution {
  public:
	int ans;
	int numTilePossibilities(string tiles) {
		int map[26];
		ans = 0;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < tiles.size(); i++) {
			map[tiles[i] - 'A']++;
		}
		dfs(map);
		return ans;
	}
	void dfs(int map[]) {
		for (int j = 0; j < 26; j++) {
			if (map[j]) {
				map[j]--;
				ans++;
				dfs(map);
				map[j]++;
			}
		}
	}
};