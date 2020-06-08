/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-07 17:17:55
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
	TreeNode* buildTree(vector<int>& po, vector<int>& io) {
		return buildTree(po, io, 0, po.size(), 0, io.size());
	}
	TreeNode* buildTree(vector<int>& po, vector<int>& io, int a0, int a1,
	                    int b0, int b1) {
		if (a0 >= a1) {
			return nullptr;
		}
		TreeNode* root = new TreeNode(po[a0]);
		int i;
		for (i = b0; i < b1 && io[i] != po[a0]; ++i);
		root->left = buildTree(po, io, a0 + 1, a0 + i - b0 + 1, b0, i);
		root->right = buildTree(po, io, a0 + i - b0 + 1, a1, i + 1, b1);
		return root;
	}
};