/**
 * @date    2020-09-02 17:45:18
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	bool canPartitionKSubsets(vector<int>& nums, int k) {
		int sum = 0;
		for (auto x : nums) {
			sum += x;
		}
		if (sum % k != 0) {
			return false;
		}
		sum = sum / k;
		sort(nums.begin(), nums.end());
		if (nums.back() > sum) {
			return false;
		}
		vector<int> v(k, sum);
		return help(nums, nums.size() - 1, v, k);
	}
	bool help(vector<int>& nums, int cur, vector<int>& v,
	          int k) {
		if (cur < 0) {
			return true;
		}

		for (int i = 0; i < k; i++) {
			//如果正好能放下当前的数或者放下当前的数后，还有机会继续放前面的数（剪枝）
			if (v[i] == nums[cur] || (v[i] - nums[cur] >= nums[0])) {
				v[i] -= nums[cur];
				//递归，开始放下一个数
				if (help(nums, cur - 1, v, k)) {
					return true;
				}
				v[i] += nums[cur];
			}
		}
		return false;
	}
};