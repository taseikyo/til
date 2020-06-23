/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 15:48:45
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
// 删除仅包含 0 的子树
class Solution {
  public:
	TreeNode* pruneTree(TreeNode* root) {
		if (!root) {
			return root;
		}
		TreeNode *dummy = new TreeNode(-1, root, nullptr);
		foo(dummy, root);
		return dummy->left;
	}
	void foo(TreeNode* &root, TreeNode* cur) {
		if (!cur) {
			return;
		}
		foo(cur, cur->left);
		foo(cur, cur->right);
		if (!cur->left && !cur->right) {
			if (cur->val == 0) {
				if (root->left == cur) {
					root->left = nullptr;
				}
				if (root->right == cur) {
					root->right = nullptr;
				}
				delete cur;
			}
		}
	}
};