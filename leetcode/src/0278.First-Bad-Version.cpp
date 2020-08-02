/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 23:12:01
 * @link    github.com/taseikyo
 */

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
  public:
	int firstBadVersion(int n) {
		int l = 1, h = n;
		while (l < h) {
			int mid = l + (h - l) / 2;
			if (isBadVersion(mid)) {
				h = mid;
			} else {
				l = mid + 1;
			}
		}
		return l;
	}
};