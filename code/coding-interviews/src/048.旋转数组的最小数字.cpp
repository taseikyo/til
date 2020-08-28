/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 20:23:02
 * @link    github.com/taseikyo
 */

// 将 mid 的值与 high 值比较，如果大，说明 mid 位于左半部分，low = mid+1
// 否则，mid 位于右半部分，mid 有可能就是最小值，所以 high = mid
class Solution {
  public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.empty()) {
			return 0;
		}
		int low = 0, high = rotateArray.size() - 1;
		while (low < high) {
			int mid = (low + high) / 2;
			if (rotateArray[mid] > rotateArray[high]) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}
		return rotateArray[low];
	}
};