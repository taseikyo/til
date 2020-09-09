/**
 * @date    2020-09-09 17:25:25
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> ans;
	vector<vector<int>> combinationSum(vector<int>& candidates,
	int target) {
		sort(candidates.begin(), candidates.end());
		for (int i = 0; i < candidates.size(); ++i) {
			vector<int> tmp{candidates[i]};
			backtrace(candidates, target, i, tmp,
			          target - candidates[i]);

		}

		return ans;
	}
	void backtrace(vector<int>& candidates,
	               int target, int cur, vector<int>& tmp, int left) {
		if (left == 0) {
			ans.push_back(tmp);
		}
		if (cur >= candidates.size()) {
			return;
		}
		if (left < candidates[cur]) {
			return;
		}
		for (int i = cur; i < candidates.size(); ++i) {
			tmp.push_back(candidates[i]);
			backtrace(candidates, target, i, tmp,
			          left - candidates[i]);
			tmp.pop_back();
		}
	}
};