/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 22:49:37
 * @link    github.com/taseikyo
 */

// 可以直接用公式算出缺的那个数
class Solution {
  public:
	int missingNumber(vector<int>& nums) {
		int n = nums.size();
		int sum = n * (n + 1) / 2;
		int foo = 0;
		for (auto c : nums) {
			foo += c;
		}
		return sum - foo;
	}
};

// 这个方法也挺有趣的
// 0 ^ 1 ^ ... n
// nums 是 0-n 缺了一个
// 异或就是缺的一个
class Solution {
  public:
	int missingNumber(vector<int>& nums) {
		int i, ans = 0;
		for (i = 0 ; i < nums.size() ; i++) {
			ans ^= i;
			ans ^= nums[i];
		}
		return ans ^ i;
	}
};