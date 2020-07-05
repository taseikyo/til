/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 22:48:37
 * @link    github.com/taseikyo
 */
// 本来想在第一次循环就直接插入并合并
// 不知道怎么做，只能先插入然后再合并
class Solution {
  public:
	vector<vector<int>> insert(vector<vector<int>>& intervals,
	vector<int>& newInterval) {
		if (intervals.empty()) {
			return vector<vector<int>> {newInterval};
		}
		int i = 0;
		for (; i < intervals.size(); ++i) {
			if (intervals[i][0] >= newInterval[0]) {
				intervals.insert(intervals.begin() + i, newInterval);
				break;
			}
		}
		if (i == intervals.size()) {
			intervals.insert(intervals.begin() + i, newInterval);
		}
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
		ans.push_back(base);
		return ans;
	}
};


// 这个方法就是我想做的，循环的时候插入合并，但是没想到
class Solution {
  public:
	vector<vector<int>> insert(vector<vector<int>>& intervals,
	vector<int>& newInterval) {
		vector<vector<int>> answer;
		bool done = false;
		for (int i = 0; i < intervals.size(); i++) {
			if (intervals[i][1] < newInterval[0]) {
				answer.push_back(intervals[i]);
			} else if (intervals[i][0] > newInterval[1]) {
				if (!done) {
					answer.push_back(newInterval);
					done = true;
				}
				answer.push_back(intervals[i]);
			} else {
				newInterval[0] = min(newInterval[0], intervals[i][0]);
				newInterval[1] = max(newInterval[1], intervals[i][1]);
			}
		}

		if (!done) {
			answer.push_back(newInterval);
		}
		return answer;
	}
};