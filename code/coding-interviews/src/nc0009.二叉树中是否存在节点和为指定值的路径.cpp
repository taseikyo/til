/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 22:17:47
 * @link    github.com/taseikyo
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
	bool hasPathSum(TreeNode *root, int sum) {
		if (nullptr == root) return false;
		else if (root->val == sum && root->left == nullptr
		         && root->right == nullptr) {
			return true;
		}
		return hasPathSum(root->left, sum - root->val)
		       || hasPathSum(root->right, sum - root->val);
	}
};