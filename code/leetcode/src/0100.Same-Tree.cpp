/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 16:04:17
 * @link    github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
  public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (!p && !q) {
			return true;
		} else if (!p || !q) {
			return false;
		}
		return (p->val == q->val) && isSameTree(p->left, q->left)
		       && isSameTree(p->right, q->right);
	}
};