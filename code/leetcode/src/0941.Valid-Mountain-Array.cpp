/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 23:21:34
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool validMountainArray(vector<int>& A) {
		if (A.size() < 3) {
			return false;
		}
		int i = 1;
		for (; i < A.size(); ++i) {
			if (A[i] < A[i - 1]) {
				break;
			}
		}
		if (i < 2 || i == A.size()) {
			return false;
		}
		for (; i < A.size(); ++i) {
			if (A[i] >= A[i - 1]) {
				return false;
			}
		}
		return true;
	}
};