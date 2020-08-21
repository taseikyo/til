/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-06 16:51:46
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
	int ans = INT_MIN;
	int maxPathSum(TreeNode* root) {
		foo(root);
		return ans;
	}
	int foo(TreeNode* root) {
		if (!root) {
			return 0;
		}
		int l = foo(root->left);
		int r = foo(root->right);
		if (l + r + root->val > ans) {
			ans = l + r + root->val;
		}
		if (r + root->val > ans) {
			ans = r + root->val;
		}
		if (l + root->val > ans) {
			ans = l + root->val;
		}
		if (root->val > ans) {
			ans = root->val;
		}
		// 由于只能单向 所以要么 左孩子-节点-父亲 要么 右孩子-节点-父亲
		int max_now = max(root->val, root->val + l);
		max_now = max(max_now, root->val + r);
		return max_now;
	}
};