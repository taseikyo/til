/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-13 22:13:13
 * @link    github.com/taseikyo
 */

class SortedStack {
  public:
	SortedStack() {
	}

	void push(int val) {
		while (s2.size() && s2.top() > val) {
			s1.push(s2.top());
			s2.pop();
		}
		while (s1.size() && s1.top() < val) {
			s2.push(s1.top());
			s1.pop();
		}
		// s2 都是比 val 小的，且从顶到底降序
		// s1 都是比 val 大的，且从顶到底升序
		s1.push(val);
	}

	void pop() {
		while (s2.size()) {
			s1.push(s2.top());
			s2.pop();
		}
		if (s1.size()) {
			s1.pop();
		}
	}

	int peek() {
		while (s2.size()) {
			s1.push(s2.top());
			s2.pop();
		}
		if (s1.size()) {
			return s1.top();
		}
		return -1;
	}

	bool isEmpty() {
		return s1.empty() && s2.empty();
	}
  private:
	// 从顶到底升序
	stack<int> s1;
	// 从顶到底降序
	stack<int> s2;
};

/**
 * Your SortedStack object will be instantiated and called as such:
 * SortedStack* obj = new SortedStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->isEmpty();
 */