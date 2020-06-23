/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 16:51:18
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
// 莫名其妙，明明跟 #814 一样，却一直报错heap-use-after-free
// 删掉 delete cur; 就ok了
class Solution {
  public:
	TreeNode* removeLeafNodes(TreeNode* root, int target) {
		if (!root) {
			return root;
		}
		TreeNode *dummy = new TreeNode(-1, root, nullptr);
		foo(dummy, root, target);
		return dummy->left;
	}
	void foo(TreeNode* &root, TreeNode* cur, int target) {
		if (!cur) {
			return;
		}
		foo(cur, cur->left, target);
		foo(cur, cur->right, target);
		if (!cur->left && !cur->right) {
			if (cur->val == target) {
				if (root->left == cur) {
					root->left = nullptr;
				}
				if (root->right == cur) {
					root->right = nullptr;
				}
			}
		}
	}
};