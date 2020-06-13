/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 16:12:04
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
	int sumEvenGrandparent(TreeNode* root) {
		int ans = 0;
		foo(root, ans);
		return ans;
	}
	void foo(TreeNode* root, int & ans) {
		if (!root) {
			return;
		}
		if (root->val % 2 == 0) {
			if (root->left) {
				if (root->left->left) {
					ans += root->left->left->val;
				}
				if (root->left->right) {
					ans += root->left->right->val;
				}
			}
			if (root->right) {
				if (root->right->left) {
					ans += root->right->left->val;
				}
				if (root->right->right) {
					ans += root->right->right->val;
				}
			}
		}
		foo(root->left, ans);
		foo(root->right, ans);
	}
};