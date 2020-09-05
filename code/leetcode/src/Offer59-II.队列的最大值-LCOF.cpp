/**
 * @date    2020-09-05 19:19:32
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class MaxQueue {
  public:
	MaxQueue() {}

	int max_value() {
		if (q.empty()) {
			return -1;
		}
		return mq.front();
	}

	void push_back(int value) {
		q.push_back(value);
		while (mq.size() && mq.back() < value) {
			mq.pop_back();
		}
		mq.push_back(value);
	}

	int pop_front() {
		if (q.empty()) {
			return -1;
		}
		if (q.front() == mq.front()) {
			mq.pop_front();
		}
		auto ret = q.front();
		q.pop_front();
		return ret;
	}
  private:
	deque<int> q;
	deque<int> mq;
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */