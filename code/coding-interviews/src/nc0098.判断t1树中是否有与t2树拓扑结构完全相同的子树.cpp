/**
 * @date    2020-09-03 19:39:00
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
  public:
	/**
	 *
	 * @param t1 TreeNode类
	 * @param t2 TreeNode类
	 * @return bool布尔型
	 */
	bool isContains(TreeNode* t1, TreeNode* t2) {
		if (!t2) {
			return true;
		}
		if (!t1) {
			return false;
		}
		if (t1->val == t2->val) {
			auto ret = help(t1, t2);
			if (ret) {
				return true;
			}
		}
		return isContains(t1->left, t2) || isContains(t1->right, t2);
	}
	bool help(TreeNode* t1, TreeNode* t2) {
		if (!t2) {
			return true;
		}
		if (!t1) {
			return false;
		}
		if (t1->val != t2->val) {
			return false;
		}
		return help(t1->left, t2->left)
		       && help(t1->right, t2->right);
	}
};