/**
 * @date    2020-09-05 19:04:35
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		if (k == 0) return {};
		vector<int> ans;
		deque<size_t> win;
		for (int i = 0; i < nums.size(); ++i) {
			while (win.size() && nums[win.back()]  < nums[i]) {
				win.pop_back();
			}
			win.push_back(i);
			if (i >= k - 1) {
				ans.push_back(nums[win.front()]);
				if (i - k + 1 == win.front()) {
					win.pop_front();
				}
			}
		}
		return ans;
	}
};