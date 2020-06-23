/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 17:32:55
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
	int sumRootToLeaf(TreeNode* root) {
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
		if (!root->left && !root->right) {
			ans += root->val;
		}
		if (root->left) {
			root->left->val += root->val * 2;
			foo(root->left, ans);
		}
		if (root->right) {
			root->right->val += root->val * 2;
			foo(root->right, ans);
		}
	}
};

// 这个 4ms，我上面那个 8ms，凭什么
class Solution {
  public:
	int result = 0;
	int sumRootToLeaf(TreeNode* root) {
		if (!root)   return 0;
		helper(root, root->val);
		return result;
	}
	void helper(TreeNode* root, int sum) {
		if (root) {
			if (!root->left && !root->right) {
				result += sum;
				return;
			}
			if (root->left)
				helper(root->left, 2 * sum + (root->left)->val);
			if (root->right)
				helper(root->right, 2 * sum + (root->right)->val);
		}
	}
};