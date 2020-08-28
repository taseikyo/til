/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 14:17:37
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=13&&tqId=11217&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
 */
class Solution {
  public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
		if (num.empty() || size == 0 || size > num.size()) {
			return{};
		}
		int idx = help(num, 0, size - 1);
		int max_num = num[idx];
		vector<int> ans{max_num};
		for (int i = size; i < num.size(); ++i) {
			if (i - size + 1 > idx) {
				idx = help(num, i - size + 1, i);
				max_num = num[idx];
			}
			if (idx != i && num[i] > max_num) {
				max_num = num[i];
				idx = i;
			}
			ans.push_back(max_num);
		}
		return ans;
	}
	// [begin, end] -> index
	int help(const vector<int>& num, int begin, int end) {
		if (begin == end) {
			return begin;
		}
		int idx = begin;
		int max_num = num[begin];
		for (int i = begin + 1; i <= end; ++i) {
			if (num[i] > max_num) {
				idx = i;
				max_num = num[i];
			}
		}
		return idx;
	}
};

// 用队列缓存数据
class Solution {
  public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
		vector<int> ret;
		if (num.size() == 0 || size < 1 || num.size() < size) return ret;
		int n = num.size();
		deque<int> dq;
		for (int i = 0; i < n; ++i) {
			while (!dq.empty() && num[dq.back()] < num[i]) {
				dq.pop_back();
			}
			dq.push_back(i);
			// 判断队列的头部的下标是否过期
			if (dq.front() + size <= i) {
				dq.pop_front();
			}
			// 判断是否形成了窗口
			if (i + 1 >= size) {
				ret.push_back(num[dq.front()]);
			}
		}
		return ret;
	}
};