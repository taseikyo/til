/**
 * @date    2020-08-22 16:35:25
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	float eps = 1e-6;
	bool judgePoint24(vector<int>& nums) {
		double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
		return judgePoint24_4(a, b, c, d);
	}

	bool judgePoint24_1(double a) {
		return abs(a - 24) < eps;
	}

	bool judgePoint24_2(double a, double& b) {
		return
		    judgePoint24_1(a + b) ||
		    judgePoint24_1(a - b) ||
		    judgePoint24_1(b - a) ||
		    judgePoint24_1(a * b) ||
		    judgePoint24_1(a / b) ||
		    judgePoint24_1(b / a);
	}

	bool judgePoint24_3(double a, double& b, double& c) {
		return
		    judgePoint24_2(b + c, a) ||
		    judgePoint24_2(b - c, a) ||
		    judgePoint24_2(c - b, a) ||
		    judgePoint24_2(b * c, a) ||
		    judgePoint24_2(b / c, a) ||
		    judgePoint24_2(c / b, a) ||
		    judgePoint24_2(a + c, b) ||
		    judgePoint24_2(a - c, b) ||
		    judgePoint24_2(c - a, b) ||
		    judgePoint24_2(a * c, b) ||
		    judgePoint24_2(a / c, b) ||
		    judgePoint24_2(c / a, b) ||
		    judgePoint24_2(a + b, c) ||
		    judgePoint24_2(a - b, c) ||
		    judgePoint24_2(b - a, c) ||
		    judgePoint24_2(a * b, c) ||
		    judgePoint24_2(a / b, c) ||
		    judgePoint24_2(b / a, c);
	}

	bool judgePoint24_4(double& a, double& b, double& c,
	                    double& d) {
		return
		    judgePoint24_3(c + d, a, b) ||
		    judgePoint24_3(c - d, a, b) ||
		    judgePoint24_3(d - c, a, b) ||
		    judgePoint24_3(d * c, a, b) ||
		    judgePoint24_3(c / d, a, b) ||
		    judgePoint24_3(d / c, a, b) ||
		    judgePoint24_3(b + d, a, c) ||
		    judgePoint24_3(b - d, a, c) ||
		    judgePoint24_3(d - b, a, c) ||
		    judgePoint24_3(b * d, a, c) ||
		    judgePoint24_3(b / d, a, c) ||
		    judgePoint24_3(d / b, a, c) ||
		    judgePoint24_3(b + c, a, d) ||
		    judgePoint24_3(b - c, a, d) ||
		    judgePoint24_3(c - b, a, d) ||
		    judgePoint24_3(b * c, a, d) ||
		    judgePoint24_3(b / c, a, d) ||
		    judgePoint24_3(c / b, a, d) ||
		    judgePoint24_3(a + d, b, c) ||
		    judgePoint24_3(a - d, b, c) ||
		    judgePoint24_3(d - a, b, c) ||
		    judgePoint24_3(a * d, b, c) ||
		    judgePoint24_3(a / d, b, c) ||
		    judgePoint24_3(d / a, b, c) ||
		    judgePoint24_3(a + c, b, d) ||
		    judgePoint24_3(a - c, b, d) ||
		    judgePoint24_3(c - a, b, d) ||
		    judgePoint24_3(a * c, b, d) ||
		    judgePoint24_3(a / c, b, d) ||
		    judgePoint24_3(c / a, b, d) ||
		    judgePoint24_3(a + b, c, d) ||
		    judgePoint24_3(a - b, c, d) ||
		    judgePoint24_3(b - a, c, d) ||
		    judgePoint24_3(a * b, c, d) ||
		    judgePoint24_3(a / b, c, d) ||
		    judgePoint24_3(b / a, c, d);
	}
};
class Solution {
  public:
	static constexpr int TARGET = 24;
	static constexpr double EPSILON = 1e-6;
	static constexpr int ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3;

	bool judgePoint24(vector<int> &nums) {
		vector<double> l;
		for (const int &num : nums) {
			l.emplace_back(static_cast<double>(num));
		}
		return solve(l);
	}

	bool solve(vector<double> &l) {
		if (l.size() == 0) {
			return false;
		}
		if (l.size() == 1) {
			return fabs(l[0] - TARGET) < EPSILON;
		}
		int size = l.size();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i != j) {
					vector<double> list2 = vector<double>();
					for (int k = 0; k < size; k++) {
						if (k != i && k != j) {
							list2.emplace_back(l[k]);
						}
					}
					for (int k = 0; k < 4; k++) {
						// 加法和乘法都满足交换律，所以只需要验证一种即可
						if (k < 2 && i > j) {
							continue;
						}
						if (k == ADD) {
							list2.emplace_back(l[i] + l[j]);
						} else if (k == MULTIPLY) {
							list2.emplace_back(l[i] * l[j]);
						} else if (k == SUBTRACT) {
							list2.emplace_back(l[i] - l[j]);
						} else if (k == DIVIDE) {
							if (fabs(l[j]) < EPSILON) {
								continue;
							}
							list2.emplace_back(l[i] / l[j]);
						}
						if (solve(list2)) {
							return true;
						}
						list2.pop_back();
					}
				}
			}
		}
		return false;
	}
};