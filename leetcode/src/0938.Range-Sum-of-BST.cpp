/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 16:34:49
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
	int rangeSumBST(TreeNode* root, int L, int R) {
		int ans = 0;
		if (root) {
			if (root->val <= R && root->val >= L) {
				ans += root->val;
			}
			if (root->val <= R) {
				ans += rangeSumBST(root->right, L, R);
			}
			if (root->val >= L) {
				ans += rangeSumBST(root->left, L, R);
			}
			return ans;
		}
		return 0;
	}
};