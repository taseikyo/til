/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:00:27
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	string frequencySort(string s) {
		// 字符：频率
		unordered_map<char, int> map;
		for (auto i : s) {
			map[i]++;
		}
		// 频率：字符集合
		vector<vector<int>> bucket(s.size() + 1);
		for (auto it = map.begin(); it != map.end(); ++it) {
			bucket[it->second].push_back(it->first);
		}
		string ans;
		for (int i = s.size(); i >= 0; --i) {
			if (bucket[i].empty()) {
				continue;
			}
			for (auto c : bucket[i]) {
				for (int j = 0; j < i; ++j) {
					ans.push_back(c);
				}
			}
		}
		return ans;
	}
};