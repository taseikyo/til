/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 22:20:29
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int missingNumber(vector<int>& nums) {
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			sum ^= i;
			sum ^= nums[i];
		}
		sum ^= nums.size();
		return sum;
	}
};