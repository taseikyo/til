/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 22:31:57
 * @link    github.com/taseikyo
 */

// 耍赖的做法，没意思
class Solution {
  public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		if (m == 0) {
			nums1 = nums2;
			return;
		}
		if (n == 0) {
			return;
		}
		for (int i = m; i < m + n; ++i) {
			nums1[i] = nums2[i - m];
		}
		sort(nums1.begin(), nums1.end());
	}
};

// 这个方法有趣，从后往前比较
class Solution {
  public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int first = m - 1;
		int second = n - 1;
		for (int i = m + n - 1; i >= 0; i--) {
			if (second < 0) {
				break;
			}
			if (first >= 0 && nums1[first] > nums2[second]) {
				nums1[i] = nums1[first];
				first--;
			} else {
				nums1[i] = nums2[second];
				second--;
			}
		}
	}
};