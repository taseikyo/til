/**
 * @date    2020-08-16 18:04:52
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class MedianFinder {
  public:
	MedianFinder() {}

	void addNum(int num) {
		if (v.empty()) {
			v.push_back(num);
		} else {
			auto it = lower_bound(v.begin(), v.end(), num);
			if (it == v.end()) {
				v.push_back(num);
			} else {
				v.insert(it, num);
			}
		}
	}

	double findMedian() {
		int n = v.size();
		if (n & 1) {
			return v[n / 2];
		}
		// 经典错误，这里返回是一个 int，最后转成 double
		// 对于[1, 2] => 1.0
		// return (v[n / 2] + v[n / 2 - 1]) / 2;
		return (v[n / 2] + v[n / 2 - 1]) / 2.0;
	}
  private:
	vector<int> v;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */