/**
 * @date    2020-08-16 16:12:06
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Foo {
  public:
	Foo() {
		m2.lock();
		m3.lock();
		m1.unlock();
	}

	void first(function<void()> printFirst) {
		m1.lock();
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		m2.unlock();
	}

	void second(function<void()> printSecond) {
		m2.lock();
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		m3.unlock();
	}

	void third(function<void()> printThird) {
		m3.lock();
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
		m1.unlock();
	}
  private:
	mutex m1, m2, m3;
};