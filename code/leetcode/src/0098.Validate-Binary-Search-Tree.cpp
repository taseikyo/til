/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 15:31:47
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
// 这个用 INT_MAX 会错，因为有测试用例是 [2147483647]
class Solution {
  public:
	bool isValidBST(TreeNode* root) {
		return isValidBST(root, LONG_MIN, LONG_MAX);
	}
	bool isValidBST(TreeNode* root, long min, long max) {
		if (!root) return true;
		if (root->val <= min || root->val >= max) return false;
		return isValidBST(root->left, min, root->val)
		       && isValidBST(root->right, root->val, max);
	}
};