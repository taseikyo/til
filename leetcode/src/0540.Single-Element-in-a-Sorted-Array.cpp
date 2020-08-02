/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 18:12:44
 * @link    github.com/taseikyo
 */

// 要求以 O(logN) 时间复杂度进行求解，因此不能遍历数组并进行异或操作来求解
// 令 index 为 Single Element 在数组中的位置
// 在 index 之后，数组中原来存在的成对状态被改变
// 如果 m 为偶数，并且 m + 1 < index，那么 nums[m] == nums[m + 1]
// m + 1 >= index，那么 nums[m] != nums[m + 1]
// 
// 如果 nums[m] == nums[m + 1]，那么 index 所在的数组位置为 [m + 2, h]
// 反之在 [l, m]
class Solution {
  public:
	int singleNonDuplicate(vector<int>& nums) {
		int l = 0, h = nums.size() - 1;
		while (l < h) {
			int m = l + (h - l) / 2;
			if (m % 2 == 1) {
				m--;   // 保证 l/h/m 都在偶数位，使得查找区间大小一直都是奇数
			}
			if (nums[m] == nums[m + 1]) {
				l = m + 2;
			} else {
				h = m;
			}
		}
		return nums[l];
	}
};