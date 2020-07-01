/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 23:40:06
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() < 2) {
			return intervals;
		}
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> ans;
		vector<int> base = intervals[0];
		for (int i = 1; i < intervals.size(); ++i) {
			if (base[1] < intervals[i][0]) {
				ans.push_back(base);
				base = intervals[i];
			} else {
				base[1] = max(intervals[i][1], base[1]);
			}
		}
		return ans;
	}
};