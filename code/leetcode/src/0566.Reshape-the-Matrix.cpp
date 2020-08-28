/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 17:08:34
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r,
	int c) {
		if (nums.size()*nums[0].size() != r * c) {
			return nums;
		}
		vector<vector<int>> ans;
		int x = 0, y = 0;
		while (r--) {
			vector<int> tmp;
			for (int i = 0; i < c; ++i) {
				if (y == nums[0].size()) {
					y = 0;
					++x;
				}
				tmp.push_back(nums[x][y++]);
			}
			ans.push_back(tmp);
		}
		return ans;
	}
};