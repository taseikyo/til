/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 22:43:45
 * @link    github.com/taseikyo
 */

// 思路很简单，但是很慢 6.43%
class Solution {
  public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() / 2];
	}
};

class Solution {
  public:
	int majorityElement(vector<int>& nums) {
		int ans, count = 0;
		for (auto num : nums) {
			if (count == 0) {
				ans = num;
			}
			count += (num == ans) ? 1 : -1;
		}
		return ans;
	}
};