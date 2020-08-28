/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-07 17:57:56
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
	int minDepth(TreeNode* root) {
		if (root == NULL) return 0;
		return dfs(root);
	}

	int dfs(TreeNode* root) {
		if (root == NULL) return INT_MAX;
		if (root->left == NULL && root->right == NULL) return 1;
		return 1 + min(dfs(root->left) , dfs(root->right));

	}
};