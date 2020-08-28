/**
 * @date    2020-08-16 17:01:11
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p,
	                               TreeNode* q) {
		if (!root) {
			return nullptr;
		}
		if (root == p || root == q) {
			return root;
		}
		TreeNode*left = lowestCommonAncestor(root->left, p, q);
		TreeNode*right = lowestCommonAncestor(root->right, p, q);
		if (left && right) {
			return root;
		}
		if (left) {
			return left;
		}
		return right;
	}
};