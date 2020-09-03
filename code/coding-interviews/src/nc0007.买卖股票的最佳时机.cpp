/**
 * @date    2020-09-03 19:34:33
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/**
	 *
	 * @param prices int整型vector
	 * @return int整型
	 */
	int maxProfit(vector<int>& prices) {
		int ans = 0, min_price = INT_MAX;
		for (auto x : prices) {
			min_price = min(min_price, x);
			ans += x - min_price;
		}
		return ans;
	}
};