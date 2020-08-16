/**
 * @date    2020-08-16 16:15:25
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class ZeroEvenOdd {
  private:
	int n;
	mutex m1, m2, m3;
  public:
	ZeroEvenOdd(int n) {
		this->n = n;
		m1.unlock();
		m2.lock();
		m3.lock();
	}

	// printNumber(x) outputs "x", where x is an integer.
	void zero(function<void(int)> printNumber) {
		for (int i = 0; i < n; ++i) {
			m1.lock();
			printNumber(0);
			if (i&1) {
				m2.unlock();
			} else {
				m3.unlock();
			}
		}

	}

	void even(function<void(int)> printNumber) {
		for (int i = 2; i <= n; i += 2) {
			m2.lock();
			printNumber(i);
			m1.unlock();
		}
	}

	void odd(function<void(int)> printNumber) {
		for (int i = 1; i <= n; i += 2) {
			m3.lock();
			printNumber(i);
			m1.unlock();
		}
	}
};