/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-05 15:47:02
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/a861533d45854474ac791d90e447bafd?tpId=13&&tqId=11176&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
 */

// 对于一个序列S，最后一个元素是根，如果去掉最后一个元素的序列为T
// 那么T满足：T可以分成两段，前一段（左子树）小于x，后一段（右子树）大于x
// 且这两段（子树）都是合法的后序序列。

class Solution {
	bool judge(vector<int>& a, int l, int r) {
		if (l >= r) return true;
		int i = r;
		while (i > l && a[i - 1] > a[r]) --i;
		for (int j = i - 1; j >= l; --j) if (a[j] > a[r]) return false;
		return judge(a, l, i - 1) && (judge(a, i, r - 1));
	}
  public:
	bool VerifySquenceOfBST(vector<int> a) {
		if (!a.size()) return false;
		return judge(a, 0, a.size() - 1);
	}
};