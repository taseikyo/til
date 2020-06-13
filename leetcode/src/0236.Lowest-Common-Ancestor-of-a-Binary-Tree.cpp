/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 15:17:30
 * @link    github.com/taseikyo
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
// 这个用 235 的递归版本方法就行
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
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (!left) return right;
		if (!right) return left;
		return root;
	}
};