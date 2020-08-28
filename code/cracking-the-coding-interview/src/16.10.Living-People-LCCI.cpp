/**
 * @date    2020-08-25 20:03:27
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	/* 利用数组记录出生时刻, 死亡时刻,    */
	/* 再根据前缀和 , 求最大值, 并标记idx */
	int maxAliveYear(vector<int>& birth, vector<int>& death) {
		int cnt[102];
		memset(cnt, 0, sizeof(int) * 102);
		int tmp = 0;
		int max = 0;
		int idx = 0;
		/* 出生年份标记1, 死亡年份下一年标记-1*/
		for (int i = 0; i < birth.size(); i++) {
			cnt[birth[i] - 1900]++;
			cnt[death[i] - 1900 + 1]--;
		}
		/* 前缀和即当前人数, 求最大值 */
		for (int i = 0; i < 101; i++) {
			tmp += cnt[i];
			if (tmp > max) {
				max = tmp;
				idx = i;
			}
		}
		return idx + 1900;
	}
};