/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 13:08:15
 * @link    github.com/taseikyo
 */

/*
max 记录 最大值
min 记录  最小值
min ,max 都不记0
满足条件 1 max - min <5
        2 除0外没有重复的数字(牌)
        3 数组长度 为5
 */
class Solution {
  public:
	bool IsContinuous(vector<int> n) {
		if (n.empty()) {
			return false;
		}
		vector<int> dp(14);
		dp[0] = -1;
		int size = n.size();
		int max = -1, min = 14;
		for (int i = 0; i < size; ++i) {
			++dp[n[i]];
			if (n[i] == 0) {
				continue;
			}
			if (dp[n[i]] > 1) {
				return false;
			}
			if (n[i] > max) {
				max = n[i];
			}
			if (n[i] < min) {
				min = n[i];
			}
		}
		if (max - min < 5) {
			return true;
		}
		return false;
	}
};