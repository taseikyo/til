/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 20:57:01
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int trap(vector<int>& height) {
		int l = 0;
		int r = height.size()-1;
		int tmp = 0;
		int ans = 0;
		while (l < r) {
			if (height[l] <= height[r]) {
				tmp = max(tmp, height[l]);
				ans += tmp - height[l++];
			} else {
				tmp = max(tmp, height[r]);
				ans += tmp - height[r--];
			}
		}
		return ans;
	}
};