/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 14:42:02
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
	TreeNode* insertIntoBST(TreeNode* root, int val) {
		if (!root) {
			TreeNode* p = new TreeNode(val);
			return p;
		}
		if (root->val > val) {
			root->left = insertIntoBST(root->left, val);
		} else {
			root->right = insertIntoBST(root->right, val);
		}
		return root;
	}
};