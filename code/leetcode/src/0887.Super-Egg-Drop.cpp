/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-23 14:52:20
 * @link    github.com/taseikyo
 */

// https://leetcode-cn.com/problems/super-egg-drop/solution/887-by-ikaruga/
class Solution {
  public:
	int calcF(int K, int T) {
		if (T == 1 || K == 1) return T + 1;
		return calcF(K - 1, T - 1) + calcF(K, T - 1);
	}

	int superEggDrop(int K, int N) {
		int T = 1;
		while (calcF(K, T) < N + 1) T++;
		return T;
	}
};

// https://leetcode-cn.com/problems/super-egg-drop/solution/ji-ben-dong-tai-gui-hua-jie-fa-by-labuladong/
class Solution {
	unordered_map<int, int> memo;
	int dp(int K, int N) {
		if (memo.find(N * 100 + K) == memo.end()) {
			int ans;
			if (N == 0) ans = 0;
			else if (K == 1) ans = N;
			else {
				int lo = 1, hi = N;
				while (lo + 1 < hi) {
					int x = (lo + hi) / 2;
					int t1 = dp(K - 1, x - 1);
					int t2 = dp(K, N - x);

					if (t1 < t2) lo = x;
					else if (t1 > t2) hi = x;
					else lo = hi = x;
				}

				ans = 1 + min(max(dp(K - 1, lo - 1), dp(K, N - lo)),
				              max(dp(K - 1, hi - 1), dp(K, N - hi)));
			}

			memo[N * 100 + K] = ans;
		}

		return memo[N * 100 + K];
	}
  public:
	int superEggDrop(int K, int N) {
		return dp(K, N);
	}
};

// https://leetcode-cn.com/problems/super-egg-drop/solution/ji-dan-diao-luo-by-leetcode-solution-2/
class Solution {
  public:
	int superEggDrop(int K, int N) {
		if (N == 1) {
			return 1;
		}
		vector<vector<int>> f(N + 1, vector<int>(K + 1));
		for (int i = 1; i <= K; ++i) {
			f[1][i] = 1;
		}
		int ans = -1;
		for (int i = 2; i <= N; ++i) {
			for (int j = 1; j <= K; ++j) {
				f[i][j] = 1 + f[i - 1][j - 1] + f[i - 1][j];
			}
			if (f[i][K] >= N) {
				ans = i;
				break;
			}
		}
		return ans;
	}
};

// 提交区 100% 的解法
class Solution {
  public:
	int superEggDrop(int K, int N) {
		// opt[moves][eggs] := using m moves and e eggs, how many floors can we check?
		// if we have known the largest number of floors we can determine using m-1 moves and e-1 eggs as opt[m-1][e-1]
		// since there exist a optimal strategy that we should start from some particular optimally chosen floor X0, if
		// the egg breaks, we can determine opt[m-1][e-1] and if it doesn't break, we can determine opt[m-1][e] floors above
		// floor x0, so including floor x0, we can determine opt[m-1][e-1] +opt[m-1][e] +1 floors

		// this is the version to simplify DP table from 2-dimensional to O(K) space
		vector<int> dp(K + 1);
		int step = 0;
		for (; dp[K] < N; step++) {
			for (int i = K; i > 0; i--)
				dp[i] = (1 + dp[i] + dp[i - 1]);
		}
		return step;
	}
};