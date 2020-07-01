/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-01 22:59:39
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<bool> kidsWithCandies(vector<int>& candies,
	                             int extraCandies) {
		int max = *max_element(candies.begin(), candies.end());
		vector<bool> ret;
		int n = candies.size();
		for (int i = 0; i < n; ++i) {
			ret.push_back(candies[i] + extraCandies >= max);
		}
		return ret;
	}
};