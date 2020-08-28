/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 20:53:32
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool findWhetherExistsPath(int n, vector<vector<int>>& graph,
	                           int start, int target) {
		// 起点: {能到的点}
		unordered_map<int, unordered_set<int>> map;
		for (auto it : graph) {
			map[it[0]].insert(it[1]);
		}
		return dfs(map, start, target);
	}
	bool dfs(unordered_map<int, unordered_set<int>>& map, int node,
	         int target) {
		auto set = map[node];
		if (set.find(target) != set.end()) {
			return true;
		}
		for (auto it = set.begin(); it != set.end(); ++it) {
			auto ret = dfs(map, *it, target);
			if (ret) {
				return true;
			}
		}
		return false;
	}
};

// 评论区的做法
class Solution {
  public:
	bool findWhetherExistsPath(int n, vector<vector<int> >& graph,
	                           int start, int target) {
		vector<vector<int> > vec(n);
		vector<bool> visited(n, 0);  // 解决自环和平行边的问题
		for (auto g : graph) {
			vec[g[0]].push_back(g[1]);
		}

		return dfs(vec, visited, start, target);
	}

	bool dfs(vector<vector<int> > &vec, vector<bool> visited, int start,
	         int target) {
		if (start == target)
			return true;

		visited[start] = true;
		for (auto v : vec[start]) {
			if (!visited[v]) {
				if (dfs(vec, visited, v, target))
					return true;
			}
		}
		return false;
	}
};