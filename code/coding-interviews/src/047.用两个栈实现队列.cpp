/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 20:18:22
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&&tqId=11158&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
 */

class Solution {
  public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		if (stack2.empty()) {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
		int ret = stack2.top();
		stack2.pop();
		return ret;
	}

  private:
	stack<int> stack1;
	stack<int> stack2;
};