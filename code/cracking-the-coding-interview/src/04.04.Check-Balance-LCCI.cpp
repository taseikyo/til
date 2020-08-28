/**
 * @date    2020-08-17 19:37:07
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
	bool isBalanced(TreeNode* root) {
		int depth;
		return isBalanced(root, depth);
	}
	bool isBalanced(TreeNode* root, int& depth) {
		if (!root) {
			depth = 0;
			return true;
		}
		int left, right;
		if (isBalanced(root->left, left)
		        && isBalanced(root->right, right)) {
			if (abs(left - right) <= 1) {
				depth = 1 + (left > right ? left : right);
				return true;
			}
		}
		return false;
	}
};