/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 20:45:02
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int multiply(int A, int B) {
		if (B == 0) {
			return 0;
		}
		if (B == 1) {
			return A;
		}
		if (A < B) {
			return multiply(B, A);
		}
		// (10, 5) => 10 + (10, 2) << 1
		if (B & 1) {
			return multiply(A, B / 2) << 1 + A;
		} else {
			return multiply(A, B / 2) << 1;
		}
	}
};