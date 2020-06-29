/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 16:52:58
 * @link    github.com/taseikyo
 */

class CustomStack {
  public:
	int *stack = nullptr;
	int size = 0;
	int capacity;
	CustomStack(int maxSize): capacity(maxSize) {
		stack = new int[maxSize];
	}

	void push(int x) {
		if (size >= capacity) {
			return;
		}
		stack[size++] = x;
	}

	int pop() {
		if (!size) {
			return -1;
		}
		return stack[--size];
	}

	void increment(int k, int val) {
		if (size < k) {
			k = size;
		}
		for (int i = 0; i < k; ++i) {
			stack[i] += val;
		}
	}
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */