/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 13:28:45
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		sort(numbers.begin(), numbers.end());
		int n = numbers.size() / 2;
		int target = numbers[n];
		int count = 1;

		for (int i = n - 1; i >= 0; --i) {
			if (numbers[i] != target) {
				break;
			}
			++count;
		}
		for (int i = n + 1; i < numbers.size(); ++i) {
			if (numbers[i] != target) {
				break;
			}
			++count;
		}
		return count > n ? target : 0;
	}
};

// 上面用到了 sort 所以时间复杂度是 O(NlogN)，下面这个是 O(N)
// 由于只有一个数字是重复的，所以两次循环，第一次找出，第二次判断次数
class Solution {
  public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		int n = numbers.size();
		if (n == 0) return 0;

		int num = numbers[0], count = 1;
		for (int i = 1; i < n; i++) {
			if (numbers[i] == num) count++;
			else count--;
			if (count == 0) {
				num = numbers[i];
				count = 1;
			}
		}
		// Verifying
		count = 0;
		for (int i = 0; i < n; i++) {
			if (numbers[i] == num) count++;
		}
		if (count * 2 > n) return num;
		return 0;
	}
};