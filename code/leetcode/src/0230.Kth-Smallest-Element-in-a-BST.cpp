/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 14:55:31
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
	int kthSmallest(TreeNode* root, int k) {
		vector<TreeNode*> v;
		while (root || v.size()) {
			while (root) {
				v.push_back(root);
				root = root->left;
			}
			k--;
			root = v.back();
			v.pop_back();
			if (!k) {
				return root->val;
			}
			root = root->right;
		}
		return 0;
	}
};