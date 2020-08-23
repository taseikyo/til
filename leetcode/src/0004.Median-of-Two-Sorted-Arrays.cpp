/**
 * @date    2020-08-23 16:13:12
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	double findMedianSortedArrays(vector<int>& nums1,
	                              vector<int>& nums2) {
		int l1 = nums1.size();
		int l2 = nums2.size();
		return (findKth(nums1, 0, l1, nums2, 0, l2,
		                (l1 + l2 + 1) / 2)
		        + findKth(nums1, 0, l1, nums2, 0, l2,
		                  (l1 + l2 + 2) / 2)) / 2.0;
	}
	int findKth(vector<int>& nums1, int st1, int ed1,
	            vector<int>& nums2, int st2, int ed2, int k) {
		int l1 = ed1 - st1;
		int l2 = ed2 - st2;
		// keep l1 < l2
		if (l1 > l2) {
			return findKth(nums2, st2, ed2, nums1, st1, ed1, k);
		}
		if (l1 == 0) {
			return nums2[st2 + k - 1];
		}
		if (k == 1) {
			return min(nums1[st1], nums2[st2]);
		}
		int idx1 = min(st1 + k / 2 - 1, ed1 - 1);
		int idx2 = min(st2 + k / 2 - 1, ed2 - 1);
		if (nums1[idx1] < nums2[idx2]) {
			return findKth(nums1, idx1 + 1, ed1, nums2, st2, ed2,
			               k - (idx1 - st1 + 1));
		}
		return findKth(nums1, st1, ed1, nums2, idx2 + 1, ed2,
		               k - (idx2 - st2 + 1));
	}
};