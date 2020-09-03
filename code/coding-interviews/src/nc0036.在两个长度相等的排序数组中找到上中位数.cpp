/**
 * @date    2020-09-03 19:47:15
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 * find median in two sorted array
	 * @param v1 int整型vector the array1
	 * @param v2 int整型vector the array2
	 * @return int整型
	 */
	int findMedianinTwoSortedAray(vector<int>& v1,
	                              vector<int>& v2) {
		int n = v1.size();
		if (n == 0) {
			return -1;
		}
		int l1 = 0, r1 = n - 1;
		int l2 = 0, r2 = n - 1;
		int mid1, mid2;
		while (l1 < r1) {
			mid1 = l1 + ((r1 - l1) >> 1);
			mid2 = l2 + ((r2 - l2) >> 1);
			int k = r1 - l1 + 1;
			if (v1[mid1] == v2[mid2]) {
				return v1[mid1];
			} else if (v1[mid1] > v2[mid2]) {
				if (k % 2 == 0) {
					r1 = mid1;
					l2 = mid2 + 1;
				} else {
					r1 = mid1;
					l2 = mid2;
				}
			} else {
				if (k % 2 == 0) {
					r2 = mid2;
					l1 = mid1 + 1;
				} else {
					r2 = mid2;
					l1 = mid1;
				}
			}
		}
		return min(v1[l1], v2[l2]);
	}
};