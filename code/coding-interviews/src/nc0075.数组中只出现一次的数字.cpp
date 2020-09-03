/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 20:54:31
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
		int n = data.size();
		if (n < 2) {
			return ;
		}
		if (data.size() == 2) {
			*num1 = data[0];
			*num2 = data[1];
			return;
		}

		int ans = data[0];
		for (int i = 1; i < n; ++i) {
			ans ^= data[i];
		}

		int bit = 1;
		while ((ans & bit) == 0) {
			bit <<= 1;
		}

		*num1 = *num2 = 0;
		for (auto x : data) {
			if (x & bit) {
				*num1 ^= x;
			} else {
				*num2 ^= x;
			}
		}
	}
};