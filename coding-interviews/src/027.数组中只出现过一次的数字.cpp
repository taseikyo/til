/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 12:39:22
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/e02fdb54d7524710a7d664d082bb7811?tpId=13&&tqId=11193&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
 */

// 最简单用哈希做，但是太无脑了，想了半天没啥好方法
// 讨论区这个解法tql
// 
// 我们首先还是先异或，剩下的数字肯定是A、B异或的结果，这个结果的二进制中的1，表现的是A和B的不同的位。
// 我们就取第一个1所在的位数，假设是第3位，接着把原数组分成两组，分组标准是第3位是否为1。
// 如此，相同的数肯定在一个组，因为相同数字所有位都相同，而不同的数，肯定不在一组。
// 然后把这两个组按照最开始的思路，依次异或，剩余的两个结果就是这两个只出现一次的数字。
class Solution {
  public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
		if (data.size() < 2)
			return;
		if (data.size() == 2) {
			*num1 = data[0];
			*num2 = data[1];
			return;
		}
		int size = data.size();
		int temp = data[0];
		for (int i = 1; i < size; i++)
			temp = temp ^ data[i];

		int index = 0;
		while ((temp & 1) == 0) {
			temp = temp >> 1;
			++index;
		}
		*num1 = *num2 = 0;
		for (int i = 0; i < size; i++) {
			if (IsBit(data[i], index))
				*num1 ^= data[i];
			else
				*num2 ^= data[i];
		}
	}
	bool IsBit(int num, int index) {
		num = num >> index;
		return (num & 1);
	}
};