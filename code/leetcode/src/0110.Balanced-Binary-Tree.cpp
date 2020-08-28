/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 13:45:35
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
	bool isBalanced(TreeNode* root) {
		if (!root) {
			return true;
		}
		int h = 0;
		return foo(root, h);
	}
	bool foo(TreeNode* root, int &h) {
		if (!root) {
			return true;
		}
		int lh = h, rh = h;
		int ans = true;
		if (root->left) {
			ans = foo(root->left, ++lh);
			if (!ans) {
				return ans;
			}
		}
		if (root->right) {
			ans = foo(root->right, ++rh);
			if (!ans) {
				return ans;
			}
		}
		if (abs(lh - rh) > 2) {
			return false;
		}
		h = max(lh, rh);
		return true;
	}
};
// 从提交去抠的答案，确实比我简单
class Solution {
  public:
	bool flag = true;
	bool isBalanced(TreeNode* root) {
		dfs(root);
		return flag;
	}

	int dfs(TreeNode* root) {
		if (root == NULL) return 0;
		int lh = 0;
		int rh = 0;
		lh = dfs(root->left) + 1;
		rh = dfs(root->right) + 1;
		if (abs(lh - rh) > 1) {
			flag = false;
			return 0;
		}
		return max(lh, rh);
	}

};