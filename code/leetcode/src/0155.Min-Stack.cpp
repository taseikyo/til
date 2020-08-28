/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-21 21:09:13
 * @link    github.com/taseikyo
 */

class MinStack {
  public:
	/** initialize your data structure here. */
	MinStack() {}

	void push(int x) {
		if (min_stk.empty()) {
			min_stk.push(x);
		} else {
			min_stk.push(min(x, min_stk.top()));
		}
		stk.push(x);
	}

	void pop() {
		min_stk.pop();
		stk.pop();
	}

	int top() {
		return stk.top();
	}

	int getMin() {
		return min_stk.top();
	}
  private:
	stack<int> stk;
	stack<int> min_stk;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */