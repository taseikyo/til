/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-16 14:08:31
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int numDecodings(string s) {
		if (s[0] == '0')return 0;
		int len = s.size();
		vector<int>dp(len + 1);
		dp[0] = 1;
		dp[1] = 1;

		for (int i = 2; i <= len; i++) {
			int one = stoi(s.substr(i - 1, 1));
			int two = stoi(s.substr(i - 2, 2));

			if (one >= 1) dp[i] = dp[i] + dp[i - 1];
			if (two >= 10 && two <= 26) dp[i] = dp[i] + dp[i - 2];
		}

		return dp[len];
	}
};