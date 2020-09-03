/**
 * @date    2020-09-03 20:13:55
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
  public:
	/**
	 *
	 * @param root TreeNode类 the root of binary tree
	 * @return int整型vector<vector<>>
	 */
	vector<int> pre;
	vector<int> in;
	vector<int> post;
	vector<vector<int>> threeOrders(TreeNode* root) {
		if (!root) {
			return {{}};
		}
		foo(root);
		return {pre, in, post};
	}
	void foo(TreeNode* root) {
		if (root) {
			pre.push_back(root->val);
			foo(root->left);
			in.push_back(root->val);
			foo(root->right);
			post.push_back(root->val);
		}
	}
};