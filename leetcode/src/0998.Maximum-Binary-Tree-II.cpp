/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-28 17:51:31
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
	TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
		if(!root) {
			root = new TreeNode(val);
			return root;
		}
		if (val > root->val) {
			TreeNode* node = new TreeNode(val);
			node->left = root;
			root = node;
			return root;
		}
		if (!root->right) {
			root->right = new TreeNode(val);
		} else {
			root->right = insertIntoMaxTree(root->right, val);
		}
		return root;
	}
};