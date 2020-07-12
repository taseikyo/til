/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:55:50
 * @link    github.com/taseikyo
 */

// 使用大顶堆跟小顶堆
class Solution {
  public:
	int maximumProduct(vector<int>& nums) {
		priority_queue<int> max_q;
		priority_queue<int, vector<int>, greater<int> > min_q;
		for (auto i : nums) {
			max_q.push(i);
			min_q.push(i);
		}
		int ans = max_q.top();
		int ans2 = ans;
		for (int i = 0; i < 2; ++i) {
			max_q.pop();
			ans *= max_q.top();
		}
		for (int i = 0; i < 2; ++i) {
			ans2 *= min_q.top();
			min_q.pop();
		}
		// 最大值为 nums.sort()
		// max(nums[-1]*nums[-2]*nums[-3], nums[0]*nums[1]*nums[-1])
		// 仅仅考虑最大三个是不对的
		// [-4,-3,-2,-1,60]
		return max(ans, ans2);
	}
};

class Solution {
  public:
	int maximumProduct(vector<int>& nums) {
		int min1 = INT_MAX, min2 = INT_MAX;
		int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
		for (int n : nums) {
			if (n <= min1) {
				min2 = min1;
				min1 = n;
			} else if (n <= min2) {
				min2 = n;
			}
			if (n >= max1) {
				max3 = max2;
				max2 = max1;
				max1 = n;
			} else if (n >= max2) {     // n lies betweeen max1 and max2
				max3 = max2;
				max2 = n;
			} else if (n >= max3) {     // n lies betwen max2 and max3
				max3 = n;
			}
		}
		return max(min1 * min2 * max1, max1 * max2 * max3);
	}
};