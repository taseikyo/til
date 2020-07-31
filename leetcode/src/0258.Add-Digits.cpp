/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-31 22:57:20
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int addDigits(int num) {
		return (num - 1) % 9 + 1;
	}
};