/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 14:04:46
 * @link    github.com/taseikyo
 */

// 两个指针移动，i 指向需要放入奇数的位置，填入前，需要后移操作
// [i, j-1] => [i+1, j]，原来 j 位置的奇数放入 i
class Solution {
  public:
	void reOrderArray(vector<int> &array) {
		int i = 0;
		for (int j = 0; j < array.size(); ++j) {
			if (array[j] & 1) {
				int tmp = array[j];
				for (int k = j - 1; k >= i; --k) {
					array[k + 1] = array[k];
				}
				array[i++] = tmp;
			}
		}
	}
};