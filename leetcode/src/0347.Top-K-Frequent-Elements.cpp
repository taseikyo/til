/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:44:13
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		// 数字：频率
		unordered_map<int, int> map;
		for (auto i : nums) {
			map[i]++;
		}
		// 频率：数字集合
		vector<vector<int>> bucket(nums.size() + 1);
		for (auto it = map.begin(); it != map.end(); ++it) {
			bucket[it->second].push_back(it->first);
		}
		vector<int> ans;
		for (int i = nums.size(); i >= 0 && ans.size() < k; --i) {
			if (bucket[i].empty()) {
				continue;
			}
			// 题目明确答案唯一，因此这里无需判断
			ans.insert(ans.end(), bucket[i].begin(), bucket[i].end());
		}
		return ans;
	}
};