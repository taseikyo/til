/**
 * @date    2020-08-23 17:27:28
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 如果左侧找到了魔术索引，就没必要递归找右侧，因为左侧的索引肯定较小
// 我们可以根据左侧递归的返回值，决定要不要递归右侧。让递归函数返回找到的魔术索引，找不到则返回 -1
// 先递归找 mid 左侧，找到就返回，没找到，再看 mid 是不是魔术索引，是就返回，不是才找右侧。时间复杂度最坏去到 O(n)

// 不重复
// Ai > i => Ai >= i+1
// => Ai+1 > i+1
// => Ai+2 > i+2
// 所以右边不可能
// 
// 有重复
// Ai > i => Ai >= i+1
// => Ai+1 >= i+1
// 有可能
class Solution {
  public:
	int findMagicIndex(vector<int>& nums) {
		return find(nums, 0, nums.size() - 1);
	}
	// [i, r]
	int find(vector<int>& nums, int l, int r) {
		if (l > r) {
			return -1;
		}
		int mid = l + (r - l) / 2;
		int ret = find(nums, l, mid - 1);
		if (ret != -1) {
			return ret;
		}
		if (nums[mid] == mid) {
			return mid;
		}
		return find(nums, mid + 1, r);
	}
};
