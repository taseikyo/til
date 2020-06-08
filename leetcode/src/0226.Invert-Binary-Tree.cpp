/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-08 23:40:38
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
	TreeNode* invertTree(TreeNode* root) {
		if (!root) {
			return root;
		}
		TreeNode* p = root->left;
		root->left = root->right;
		root->right = p;
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};