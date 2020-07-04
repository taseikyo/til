/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 14:56:25
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/6a296eb82cf844ca8539b57c23e6e9bf?tpId=13&&tqId=11182&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。
 */

// 利用快排的思路
class Solution {
  public:
	int Partition(vector<int>& input, int begin, int end) {
		int low = begin;
		int high = end;

		int pivot = input[low];
		while (low < high) {
			while (low < high && pivot <= input[high])
				high--;
			input[low] = input[high];
			while (low < high && pivot >= input[low])
				low++;
			input[high] = input[low];
		}
		input[low] = pivot;
		return low;
	}

	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {

		int len = input.size();
		if (len == 0 || k > len || k <= 0) return {};
		if (len == k) return input;

		int start = 0;
		int end = len - 1;
		int index = Partition(input, start, end);
		while (index != (k - 1)) {
			if (index > k - 1) {
				end = index - 1;
				index = Partition(input, start, end);
			} else {
				start = index + 1;
				index = Partition(input, start, end);
			}
		}

		vector<int> res(input.begin(), input.begin() + k);

		return res;
	}

};