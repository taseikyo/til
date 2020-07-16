/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 15:47:29
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int maxProfit(vector<int>& prices) {
		int minprice = INT_MAX;
		int maxprofit = 0;
		for (int i = 0; i < prices.size(); i++) {
			if (prices[i] < minprice)
				minprice = prices[i];
			else if (prices[i] - minprice > maxprofit)
				maxprofit = prices[i] - minprice;
		}
		return maxprofit;
	}
};