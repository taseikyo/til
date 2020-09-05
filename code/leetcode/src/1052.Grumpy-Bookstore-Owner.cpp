/**
 * @date    2020-09-05 16:39:02
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 相当于记录所有窗口中最大的生气的窗口，然后在这个窗口内不生气
class Solution {
  public:
	int maxSatisfied(vector<int>& customers, vector<int>& grumpy,
	                 int X) {
		int maxAngry = 0, satisfy = 0, angry = 0, left = 0,
		    right = 0;
		while (right < customers.size()) {
			//遍历的同时累加不生气的顾客总数
			//并且向滑动窗口中添加生气的顾客数量
			if (grumpy[right] == 0)
				satisfy += customers[right];
			else
				angry += customers[right];
			right++;

			//当窗口大小超过X时，从窗口左侧减去生气的顾客数量并持续缩小窗口到X
			//注：只有生气的才要减
			while (right - left > X) {
				if (grumpy[left] == 1)
					angry -= customers[left];
				left++;
			}
			//窗口缩小完成后更新当前窗口内的生气顾客数量至最大值并等待下一轮的比较
			if (maxAngry < angry) maxAngry = angry;
		}
		return satisfy + maxAngry;
	}
};