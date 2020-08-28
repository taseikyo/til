/**
 * @date    2020-08-25 20:45:47
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int majorityElement(vector<int>& nums) {
		// 投票算法
		int temp = nums[0];
		int count = 1;
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] == temp) {
				count++;
			} else {
				count--;
			}
			if (count == 0) {
				temp = nums[i];
				count = 1;
			}
		}

		// 验证是否满足要求
		int t = nums.size() / 2 + 1;
		count = 0;
		for (int num : nums) {
			if (num == temp) count++;
			if (count == t) return temp;
		}
		return -1;
	}
};