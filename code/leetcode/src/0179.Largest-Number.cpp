/**
 * @date    2020-08-26 20:48:07
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	string largestNumber(vector<int>& nums) {
		if (nums.empty()) return "";

		sort(nums.begin(), nums.end(),
		[](int a, int b) {
			return to_string(a) + to_string(b) >
			       to_string(b) + to_string(a);
		});
		if (nums[0] == 0) return "0";

		string ans;
		for (int num : nums) ans += to_string(num);
		return ans;
	}
};