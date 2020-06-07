/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 16:24:03
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
	TreeNode* searchBST(TreeNode* root, int val) {
		if (!root || root->val == val) {
			return root;
		} else if (root->val > val) {
			return searchBST(root->left, val);
		}
		return searchBST(root->right, val);
	}
};