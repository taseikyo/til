/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 21:44:07
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
// 46.8% 看了提交区最快的，跟我的一毛一样...
class Solution {
  public:
    int ans = 0;
	TreeNode* bstToGst(TreeNode* root) {
		if (root) {
			bstToGst(root->right);
            root->val += ans;
            ans = root->val;
			bstToGst(root->left);
		}
        return root;
	}
};