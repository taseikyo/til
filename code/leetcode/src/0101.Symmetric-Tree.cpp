/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 15:56:22
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
	bool isSymmetric(TreeNode* root) {
		if (!root) {
			return true;
		}
		return isSymmetric(root->left, root->right);
	}
	bool isSymmetric(TreeNode* left, TreeNode* right) {
		if (!left && !right) {
			return true;
		} else if (!left || !right) {
			return false;
		}
		return (left->val == right->val)
		       && isSymmetric(left->left, right->right)
		       && isSymmetric(left->right, right->left);
	}
};