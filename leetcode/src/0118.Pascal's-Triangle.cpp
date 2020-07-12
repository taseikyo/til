/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:03:30
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> ans;
		for (int i = 1; i <= numRows; ++i) {
			vector<int> tmp(i, 1);
			for (int j = 1; j < i - 1; ++j) {
				tmp[j] = ans[i - 2][j - 1] + ans[i - 2][j];
			}
			ans.push_back(tmp);
		}
		return ans;
	}
};