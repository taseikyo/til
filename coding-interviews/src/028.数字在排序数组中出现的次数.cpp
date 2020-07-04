/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 12:50:49
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&&tqId=11190&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 统计一个数字在排序数组中出现的次数。
 */

class Solution {
  public:
	int GetNumberOfK(vector<int> data , int k) {
		if (data.empty()) {
			return 0;
		}
		int pos = help(data, k);
		if (pos == -1) {
			return 0;
		}
		int ans = 1;
		for (int i = pos - 1; i >= 0; --i) {
			if (data[i] == k) {
				++ans;
			} else {
				break;
			}
		}
		for (int i = pos + 1; i < data.size(); ++i) {
			if (data[i] == k) {
				++ans;
			} else {
				break;
			}
		}
		return ans;
	}
	int help(vector<int> &data , int k) {
		int low = 0;
		int high = data.size() - 1;
		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (data[mid] == k) {
				return mid;
			} else if (data[mid] > k) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		return -1;
	}
};

// 评论区看到一个牛逼写法
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        auto resultPair = equal_range(data.begin(), data.end(),k);
        return resultPair.second - resultPair.first;
    }
};