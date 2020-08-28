/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-13 15:49:43
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
		vector<int> result;
		for (int i = 0; i < index.size(); i++) {
			result.insert(result.begin() + index[i], nums[i]);
		}
		return result;
	}
};