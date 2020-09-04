/**
 * @date    2020-09-04 15:46:17
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

#include <unordered_map>

class Solution {
  public:
	/**
	 *
	 * @param v int整型vector the vay
	 * @return int整型
	 */
	int maxLength(vector<int>& v) {
		int n = v.size();
		if (n < 2) {
			return n;
		}

		// val: idx
		unordered_map<int, int> umap;

		umap[v[0]] = 0;
		int left  = 0;
		int max_len = 1;

		for (int i = 1; i < n; ++i) {
			auto iter = umap.find(v[i]);
			if (iter != umap.end()) {
				if (iter->second < left) {
					iter->second = i;
					max_len = max(max_len, i - left + 1);
				} else {
					left = iter->second + 1;
					iter->second = i;
				}
			} else {
				umap[v[i]] = i;
				max_len = max(max_len, i - left + 1);
			}
		}
		return max_len;
	}
};

#include <unordered_map>;
class Solution {
  public:
	/**
	 *
	 * @param arr int整型vector the array
	 * @return int整型
	 */
	int maxLength(vector<int>& arr) {
		if (arr.empty() == true)
			return 0;

		unordered_map<int, int> m;
		int res = 0;
		int left = -1;
		for (int i = 0; i < arr.size(); i++) {
			if (m.count(arr[i]) > 0 && m[arr[i]] > left)
				left = m[arr[i]];

			m[arr[i]] = i;
			res = max(res, i - left);
		}
		return res;
	}
};