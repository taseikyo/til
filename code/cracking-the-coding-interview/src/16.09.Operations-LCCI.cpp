/**
 * @date    2020-08-16 18:27:13
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Operations {
  public:
	Operations() {}

	int minus(int a, int b) {
		return a + ~b + 1;
	}

	int multiply(int a, int b) {
		for (int i = 0; i < b; ++i) {
			a += a;
		}
		return a;
	}

	int divide(int a, int b) {

	}
};

/**
 * Your Operations object will be instantiated and called as such:
 * Operations* obj = new Operations();
 * int param_1 = obj->minus(a,b);
 * int param_2 = obj->multiply(a,b);
 * int param_3 = obj->divide(a,b);
 */