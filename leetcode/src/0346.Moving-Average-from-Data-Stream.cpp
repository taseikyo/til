/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 17:05:24
 * @link    github.com/taseikyo
 */

class MovingAverage {
  public:
	queue<int> q;
	int capacity;
	double sum = 0;
	MovingAverage(int size): capacity(size) {
	}

	double next(int val) {
		if (q.size() >= size) {
			sum -= q.front(); q.pop();
		}
		q.push(val);
		sum += val;
		return sum / q.size();
	}
};