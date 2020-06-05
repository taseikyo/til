/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 16:25:54
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/8b3b95850edb4115918ecebdf1b4d222?tpId=13&&tqId=11192&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入一棵二叉树，判断该二叉树是否是平衡二叉树。
 * 在这里，我们只需要考虑其平衡性，不需要考虑其是不是排序二叉树
 */

class Solution {
  public:
	bool IsBalanced_Solution(TreeNode* root) {
		int h;
		return IsBalanced_Solution(root, &h);
	}
	bool IsBalanced_Solution(TreeNode *root, int *height) {
		if (not root) {
			*height = 0;
			return true;
		}
		int leftHeight, rightHeight;
		bool leftBalance = IsBalanced_Solution(root->left, &leftHeight);
		bool rightBalance = IsBalanced_Solution(root->right, &rightHeight);
		*height = max(leftHeight, rightHeight) + 1;
		if (not leftBalance || not rightBalance) {
			return false;
		}
		int diff = leftHeight - rightHeight;
		if (diff < -1 || diff > 1) {
			return false;
		} else {
			return true;
		}
	}
};