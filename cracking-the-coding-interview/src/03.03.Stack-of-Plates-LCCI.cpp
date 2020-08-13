/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-13 21:03:16
 * @link    github.com/taseikyo
 */

class StackOfPlates {
  public:
	StackOfPlates(int cap) {
		capacity = cap;
	}

	void push(int val) {
		if (capacity == 0) {
			return;
		}
		if (v.empty() || (v[cur].size() == capacity)) {
			stack<int> s;
			s.push(val);
			++cur;
			v.push_back(s);
		} else {
			v[cur].push(val);
		}
	}

	int pop() {
		if (v.empty()) {
			return -1;
		}
		int x = v[cur].top();
		v[cur].pop();
		if (v[cur].empty()) {
			v.pop_back();
			--cur;
		}
		return x;
	}

	int popAt(int index) {
		if (v.empty() || index > cur) {
			return -1;
		}
		int x = v[index].top();
		v[index].pop();
		if (v[index].empty()) {
			v.erase(v.begin() + index);
			--cur;
		}
		return x;
	}
  private:
	vector<stack<int>> v;
	int capacity;
	int cur = -1;
};

/**
 * Your StackOfPlates object will be instantiated and called as such:
 * StackOfPlates* obj = new StackOfPlates(cap);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAt(index);
 */