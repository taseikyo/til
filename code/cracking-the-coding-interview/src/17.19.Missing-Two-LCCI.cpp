/**
 * @date    2020-08-16 17:05:47
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// a + b = n(n+1)/2 - sum(nums)
// a^2 + b^2 = n(n+1)(2n+1)/6 - squre_sum(nums)
class Solution {
  public:
	vector<int> missingTwo(vector<int>& nums) {
		int n = nums.size() + 2;
		int X = n * (n + 1) / 2;
		int Y = X * (n << 1 + 1) / 3;
		for (auto i : nums) {
			X -= i;
			Y -= i * i;
		}
		// a+b = X
		// a^2+b^2 = Y
		// ab = (X^2-Y)/2
	}
};

class Solution {
  public:
	vector<int> missingTwo(vector<int>& nums) {
		int n = nums.size() + 2;
		long sum = 0;
		for (auto x : nums) sum += x;

		int sumTwo = n * (n + 1) / 2 - sum, limits = sumTwo / 2;
		sum = 0;
		for (auto x : nums)
			if (x <= limits)
				sum += x; // 两个数不相同那么一个大于，一个小于
		int one = limits * (limits + 1) / 2 - sum;
		return {one, sumTwo - one};
	}
};

//利用异或特性
class Solution {
  public:
	vector<int> missingTwo(vector<int>& nums) {
		int x = 0;
		for (int i : nums) x ^= i;
		for (int i = 1; i <= nums.size() + 2; i++) x ^= i;
		// 这里是拿到最后一个 1
		int diff = x & (-x);
		int onenum = 0;
		for (int i : nums) {
			if (diff & i) onenum ^= i;
		}
		for (int i = 1; i <= nums.size() + 2; i++) {
			if (diff & i) onenum ^= i;
		}
		return vector<int> {onenum, onenum ^ x};
	}
};