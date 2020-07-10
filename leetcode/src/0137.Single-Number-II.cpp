/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:28:27
 * @link    github.com/taseikyo
 */

// https://leetcode.com/problems/single-number-ii/discuss/43381/Clean-C%2B%2B-solution-for-generic-K
// 太强了，直接一个通用的方法
// 对于 32 位，每一位进行测试
// 除了一个数其他数都重复 k 次，则必然某些位是 n*k + 1 的
// 通过 %k 判断这一位就拿到 特别的数 所有位
class Solution {
  public:
	int singleNumber(vector<int>& nums) {
		auto r = 0, k = 3;
		for (auto i = 0; i < 32; ++i) {
			auto mask = 1 << i, cnt = 0;

			for (auto num : nums)
				cnt += bool(num & mask);

			if (cnt % k)
				r |= mask;
		}
		return r;
	}
};

// 提交区最快的解法，没看懂
class Solution {
  public:
	int singleNumber(vector<int>& nums) {
		// Using XOR + AND combination
		int ones = 0;
		int twos = 0;
		for (auto ele : nums) {
			ones = (ones ^ ele) & (~twos);
			twos = (twos ^ ele) & (~ones);
		}
		cout<<twos;
		return ones;
	}
};