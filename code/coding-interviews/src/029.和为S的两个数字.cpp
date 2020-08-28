/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 12:57:33
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/390da4f7a00f44bea7c2f3d19491311b?tpId=13&&tqId=11195&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 题目描述
输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
输出描述:
对应每个测试案例，输出两个数，小的先输出。
 */
// 找到第一队就是乘积最小的（相差越大乘积越小）
class Solution {
  public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		vector<int> ans;
		int low = 0, high = array.size() - 1;
		while (low < high) {
			if (array[low] + array[high] == sum) {
				ans = {array[low], array[high]};
				break;
			}
			while (low < high && array[low] + array[high] > sum) --high;
			while (low < high && array[low] + array[high] < sum) ++low;
		}
		return ans;
	}
};