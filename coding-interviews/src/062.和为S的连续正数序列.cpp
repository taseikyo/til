/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:48:00
 * @link    github.com/taseikyo
 */

// 暴力
class Solution {
  public:
	vector<vector<int> > FindContinuousSequence(int sum) {
		vector<vector<int>> ret;
		// 左边界
		for (int i = 1; i <= sum / 2; ++i) {
			// 右边界
			for (int j = i + 1; j < sum; ++j) {
				int tmp = 0;
				// 求区间和
				for (int k = i; k <= j; ++k) {
					tmp += k;
				}
				if (sum == tmp) {
					vector<int> ans;
					for (int k = i; k <= j; ++k) ans.push_back(k);
					ret.push_back(ans);
				} else if (tmp > sum) {
					break;
				}
			}
		}
		return ret;
	}
};

// 前缀和
class Solution {
  public:
	vector<vector<int> > FindContinuousSequence(int sum) {
		vector<vector<int>> ret;
		int tmp = 0;
		for (int i = 1; i <= sum / 2; ++i) {
			for (int j = i; j < sum; ++j) {
				tmp += j;
				if (sum == tmp) {
					vector<int> ans;
					for (int k = i; k <= j; ++k) ans.push_back(k);
					ret.push_back(ans);
				} else if (tmp > sum) {
					// 提前剪枝
					tmp = 0;
					break;
				}
			}
		}
		return ret;
	}
};

// 滑动窗口
// [l, r)
class Solution {
  public:
	vector<vector<int> > FindContinuousSequence(int sum) {
		vector<vector<int>> ret;
		int l = 1, r = 1;
		int tmp = 0;
		while (l <= sum / 2) {
			if (tmp < sum) {
				tmp += r;
				++r;
			} else if (tmp > sum) {
				tmp -= l;
				++l;
			} else {
				vector<int> ans;
				for (int k = l; k < r; ++k)
					ans.push_back(k);
				ret.push_back(ans);
				tmp -= l;
				++l;
			}
		}
		return ret;
	}
};