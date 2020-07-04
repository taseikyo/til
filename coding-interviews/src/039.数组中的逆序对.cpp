/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 15:59:50
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/96bd6684e04a44eb80e6a68efc0ec6c5?tpId=13&&tqId=11188&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007
 */

// 想不到想不到，在 merge 过程中，左右两端都是有序的
// 所以当 左边一个 i > 右边一个 j，意味着从（i-mid）都是大于 j 的所以有 mid - i + 1 个逆序对
class Solution {
  private:
	const int kmod = 1000000007;
  public:
	int InversePairs(vector<int> data) {
		int ret = 0;
		merge_sort__(data, 0, data.size() - 1, ret);
		return ret;
	}


	void merge_sort__(vector<int> &arr, int l, int r, int &ret) {
		if (l >= r) {
			return;
		}

		int mid = l + ((r - l) >> 1);
		merge_sort__(arr, l, mid, ret);
		merge_sort__(arr, mid + 1, r, ret);
		merge__(arr, l, mid, r, ret);
	}

	void merge__(vector<int> &arr, int l, int mid, int r, int &ret) {
		vector<int> tmp(r - l + 1);
		int i = l, j = mid + 1, k = 0;

		while (i <= mid && j <= r) {
			if (arr[i] > arr[j]) {
				tmp[k++] = arr[j++];
				// 奥妙之处
				ret += (mid - i + 1);
				ret %= kmod;
			} else {
				tmp[k++] = arr[i++];
			}
		}

		while (i <= mid) {
			tmp[k++] = arr[i++];
		}
		while (j <= r) {
			tmp[k++] = arr[j++];
		}

		for (k = 0, i = l; i <= r; ++i, ++k) {
			arr[i] = tmp[k];
		}
	}
};