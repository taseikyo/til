/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 23:02:47
 * @link    github.com/taseikyo
 */
// 21.01%
class Solution {
  public:
	int pivotIndex(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return n - 1;
		}
		// 前缀和
		vector<int> v(n, 0);
		v[0] = nums[0];
		for (int i = 1; i < n; ++i) {
			v[i] = v[i - 1] + nums[i];
		}
		// 有特殊情况 如 [-1,-1,-1,0,1,1]
		if (v[n - 1] - v[0] == 0) {
			return 0;
		}
		for (int i = 1; i < n; ++i) {
			if (v[i - 1] == v[n - 1] - v[i]) {
				return i;
			}
		}
		return -1;
	}
};

// 这个有点东西
class Solution {
  public:
	int pivotIndex(vector<int>& nums) {
		int fullSum = 0;
		int leftSum = 0;
		if (nums.size() == 1) return 0;
		if (nums.size() == 0) return -1;

		for (auto i : nums) fullSum += i;

		for (int i = 0; i < nums.size(); ++i) {
			fullSum -= nums[i];
			if (fullSum == leftSum ) {
				return i;
			}
			leftSum += nums[i];
		}
		return -1;
	}
};