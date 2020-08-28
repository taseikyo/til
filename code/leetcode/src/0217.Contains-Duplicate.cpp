/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 22:51:59
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool containsDuplicate(vector<int>& nums) {
		return nums.size() > set<int>(nums.begin(), nums.end()).size();
	}
};

class Solution {
  public:
	bool containsDuplicate(vector<int>& nums) {
		ios::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
		if (nums.empty())
			return false;
		int maxe = *max_element(nums.begin(), nums.end());
		int mine = *min_element(nums.begin(), nums.end());
		vector<int> temp(maxe - mine + 1, 0);
		for (int i = 0; i < nums.size(); i++) {
			if (temp[nums[i] - mine] == 1)
				return true;
			temp[nums[i] - mine]++;
		}
		return false;
	}
};