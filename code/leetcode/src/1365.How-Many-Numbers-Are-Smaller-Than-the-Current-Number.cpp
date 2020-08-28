/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 23:05:50
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
		vector<int> cnt(101, 0);
		vector<int> vec((int)nums.size(), 0);
		for (int i = 0; i < (int)nums.size(); ++i) {
			cnt[nums[i]]++;
		}
		for (int i = 1; i <= 100; ++i) cnt[i] += cnt[i - 1]; // 求前缀和
		for (int i = 0; i < (int)nums.size(); ++i) {
			if (nums[i]) vec[i] = cnt[nums[i] - 1];
		}
		return vec;
	}
};