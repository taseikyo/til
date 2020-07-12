/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 15:39:09
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> cache;
		for (int i = 0; i < nums.size(); i++) {
			auto iter = cache.find(target - nums[i]);
			if (iter != cache.end()) {
				return vector<int> {iter->second, i};
			} else {
				cache[nums[i]] = i;
			}
		}
		return vector<int> {0, 1};
	}
};