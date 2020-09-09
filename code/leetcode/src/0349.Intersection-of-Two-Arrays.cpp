/**
 * @date    2020-09-09 19:40:45
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<int> intersection(vector<int>& nums1,
	                         vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int i = 0, j = 0;
		vector<int> ans;
		while (i < nums1.size() && j < nums2.size()) {
			if (nums1[i] == nums2[j]) {
				if (ans.empty() || nums1[i] != ans.back()) {
					ans.push_back(nums1[i]);
				}
				++i, ++j;
			} else if (nums1[i] > nums2[j]) {
				++j;
			} else {
				++i;
			}
		}
		return ans;
	}
};

class Solution {
  public:
	vector<int> intersection(vector<int>& nums1,
	                         vector<int>& nums2) {
		unordered_set<int> cache;
		vector<int> res;
		for (auto x : nums1) cache.insert(x);
		for (auto x : nums2)
			if (cache.count(x)) {
				cache.erase(x);
				res.push_back(x);
			}

		return res;
	}
};