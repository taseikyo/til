/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 20:02:14
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/4c776177d2c04c2494f2555c9fcc1e49?tpId=13&&tqId=11173&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。
 * 注意：保证测试中不会当栈为空的时候，对栈调用pop()或者min()或者top()方法。
 */

// 双栈法，一个正常的栈，一个最小栈
class Solution {
  public:
	stack<int> normal, minval;
	void push(int value) {
		normal.push(value);
		if (minval.empty()) {
			minval.push(value);
		} else {
			if (value <= minval.top()) {
				minval.push(value);
			} else {
				minval.push(minval.top());
			}
		}
	}
	void pop() {
		normal.pop();
		minval.pop();
	}
	int top() {
		return normal.top();
	}
	int min() {
		return minval.top();
	}
};