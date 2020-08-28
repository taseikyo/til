/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-09 22:54:07
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> nextGreaterElement(vector<int>& nums1,
	                               vector<int>& nums2) {
		if (nums1.empty()) {
			return {};
		}
		unordered_map<int, int> m;
		stack<int> s;
		for (auto i : nums2) {
			m[i] = -1;
			if (s.empty()) {
				s.push(i);
			} else {
				while (s.size() && i > s.top()) {
					m[s.top()] = i;
					s.pop();
				}
				s.push(i);
			}
		}
		for (int i = 0; i < nums1.size(); ++i) {
			nums1[i] = m[nums1[i]];
		}
		return nums1;
	}
};