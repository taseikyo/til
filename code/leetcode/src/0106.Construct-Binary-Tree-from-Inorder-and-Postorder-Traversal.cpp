/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-07 17:41:31
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
	TreeNode* buildTree(vector<int>& io, vector<int>& po) {
		return buildTree(io, po, 0, io.size(), 0, po.size());
	}
	TreeNode* buildTree(vector<int>& io, vector<int>& po, int a0, int a1,
	                    int b0, int b1) {
		if (a0 >= a1) {
			return nullptr;
		}
		TreeNode* root = new TreeNode(po[b1 - 1]);
		int i;
		for (i = a0; i < a1 && io[i] != po[b1 - 1]; ++i);
		root->left = buildTree(io, po, a0, i, b0, b0 + i - a0);
		root->right = buildTree(io, po, i + 1, a1, b0 + i - a0, b1 - 1);
		return root;
	}
};