/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 15:40:17
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() < 2) {
			return nums.size();
		}
		int i = 0, j = 0, ans = 1;
		while (j < nums.size()) {
			if (nums[i] != nums[j]) {
				++i;
				++ans;
				nums[i] = nums[j];
			}
			++j;
		}
		// ans = i + 1，所以这里没必要
		return ans;
	}
};