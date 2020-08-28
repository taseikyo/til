/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 15:43:12
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
	int sumOfLeftLeaves(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int ans = 0;
		foo(root, ans);
		return ans;
	}
	void foo(TreeNode* root, int& ans) {
		if (!root) {
			return;
		}
		if (root->left) {
			if (!root->left->left && !root->left->right) {
				ans += root->left->val;
			}
			foo(root->left, ans);
		}
		if (root->right) {
			foo(root->right, ans);
		}
	}
};