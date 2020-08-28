/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:43:36
 * @link    github.com/taseikyo
 */

// 最简单就是排序 然后隔俩取一
class Solution {
  public:
	int arrayPairSum(vector<int>& nums) {
		int ans = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i += 2) {
			ans += nums[i];
		}
		return ans;
	}
};

// 评论区的一个解法，很容易理解，记录所有值和频率，依旧隔俩取一
class Solution {
  public:
	int arrayPairSum(vector<int>& nums) {
		vector<int> hashtable(20001, 0);
		for (size_t i = 0; i < nums.size(); i++) {
			hashtable[nums[i] + 10000]++;
		}
		int ret = 0;
		int flag = 0;
		for (size_t i = 0; i < 20001;) {
			if ((hashtable[i] > 0) && (flag == 0)) {
				ret = ret + i - 10000;
				flag = 1;
				hashtable[i]--;
			} else if ((hashtable[i] > 0) && (flag == 1)) {
				hashtable[i]--;
				flag = 0;
			} else i++;
		}
		return ret;
	}
};
// 提交区的解法，没看懂 lena_hai
class Solution {
  public:
	int arrayPairSum(vector<int>& arr) {
		int n = arr.size();
		vector<int>freq(20001, 0);

		for (int i = 0; i < n; i++) {
			freq[arr[i] + 10000]++;
		}

		int sum = 0;
		int lena_hai = 0;
		for (int i = 0; i < freq.size(); i++) {
			sum += ((freq[i] + 1 - lena_hai) / 2) * (i - 10000);
			lena_hai = (2 + freq[i] - lena_hai) % 2;
		}

		return sum;

	}
};