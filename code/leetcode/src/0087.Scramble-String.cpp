/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-15 23:03:16
 * @link    github.com/taseikyo
 */

// 牛逼的方法，首先判断是否相等，然后判断字母出现的频率
// 最后就遍历所有可能的拆分情况
class Solution {
  public:
	bool isScramble(string s1, string s2) {
		if (s1 == s2)
			return true;

		int len = s1.length();
		int count[26] = {0};
		for (int i = 0; i < len; i++) {
			count[s1[i] - 'a']++;
			count[s2[i] - 'a']--;
		}

		for (int i = 0; i < 26; i++) {
			if (count[i] != 0)
				return false;
		}

		for (int i = 1; i <= len - 1; i++) {
			if ( isScramble(s1.substr(0, i), s2.substr(0, i))
			        && isScramble(s1.substr(i), s2.substr(i)))
				return true;
			if ( isScramble(s1.substr(0, i), s2.substr(len - i))
			        && isScramble(s1.substr(i), s2.substr(0, len - i)))
				return true;
		}
		return false;
	}
};

// 动态规划
// dp[len][i][j] 来表示 s1[i, i+len) 和 s2[j, j+len) 两个字符串是否满足条件
// dp[len][i][j] = dp[q][i][j] && dp[len-q][i+q][j+q] -> S1 的左半部分和 S2 的左半部分以及 S1 的右半部分和 S2 的右半部分
// dp[len][i][j] = dp[q][i][j+len-q] && dp[len-q][i+q][j] -> S1 的右半部分和 S2 的左半部分以及 S1 的左半部分和 S2 的右半部分
class Solution {
  public:
	bool isScramble(string s1, string s2) {
		if (s1 == s2)
			return true;

		int len = s1.length();
		int count[26] = {0};
		for (int i = 0; i < len; i++) {
			count[s1[i] - 'a']++;
			count[s2[i] - 'a']--;
		}

		for (int i = 0; i < 26; i++) {
			if (count[i] != 0)
				return false;
		}
		int length = s1.length();
		bool dp[length + 1][length][length];
		for (int len = 1; len <= length; len++) {
			//S1 开始的地方
			for (int i = 0; i + len <= length; i++) {
				//S2 开始的地方
				for (int j = 0; j + len <= length; j++) {
					//长度是 1 无需切割
					if (len == 1) {
						dp[len][i][j] = s1[i] == s2[j];
					} else {
						//遍历切割后的左半部分长度
						for (int q = 1; q < len; q++) {
							dp[len][i][j] = dp[q][i][j] && dp[len - q][i + q][j + q]
							                || dp[q][i][j + len - q] && dp[len - q][i + q][j];
							//如果当前是 true 就 break，防止被覆盖为 false
							if (dp[len][i][j]) {
								break;
							}
						}
					}
				}
			}
		}
		return dp[length][0][0];
	}
};