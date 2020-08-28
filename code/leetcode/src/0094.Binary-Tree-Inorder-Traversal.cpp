/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 14:30:32
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
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> v;
		inorderTraversal(root, v);
		return v;
	}

	void inorderTraversal(TreeNode* root, vector<int> & v) {
		if (root) {
			inorderTraversal(root->left, v);
			v.push_back(root->val);
			inorderTraversal(root->right, v);
		}
	}
};