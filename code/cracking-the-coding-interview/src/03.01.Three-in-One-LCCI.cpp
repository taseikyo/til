/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-13 19:50:26
 * @link    github.com/taseikyo
 */

// 这个题目表述很迷，总之是用一个数组实现三个栈
class TripleInOne {
  public:
	TripleInOne(int stackSize) {
		capacity = stackSize;
		array.resize(stackSize * 3);
		pointer.resize(3);
		for (int i = 0; i < 3; ++i) {
			pointer[i].first = pointer[i].second = stackSize * i;
		}
	}

	void push(int stackNum, int value) {
		auto& p = pointer[stackNum];
		if (p.second - p.first == capacity) {
			return;
		}
		array[p.second++] = value;
	}

	int pop(int stackNum) {
		auto& p = pointer[stackNum];
		if (p.second == p.first) {
			return -1;
		}
		return array[--p.second];
	}

	int peek(int stackNum) {
		auto& p = pointer[stackNum];
		if (p.second == p.first) {
			return -1;
		}
		return array[p.second-1];
	}

	bool isEmpty(int stackNum) {
		return pointer[stackNum].first == pointer[stackNum].second;
	}
  private:
	// 三个栈
	vector<int> array;
	// 表示每个栈的<起点，当前点>
	vector<pair<int, int>> pointer;
	int capacity;
};

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */