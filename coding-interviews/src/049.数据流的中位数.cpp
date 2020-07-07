/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 20:36:54
 * @link    github.com/taseikyo
 */

// 插入的时候就保证有序
class Solution {
  public:
	vector<int> v;
	void Insert(int num) {
		if (v.empty()) {
			v.push_back(num);
		} else {
			auto it = lower_bound(v.begin(), v.end(), num);
			v.insert(it, num);
		}
	}

	double GetMedian() {
		int sz = v.size();
		if (sz & 1) {
			return double(v[sz >> 1]);
		}
		return double(v[sz >> 1] + v[(sz - 1) >> 1]) / 2;
	}
};