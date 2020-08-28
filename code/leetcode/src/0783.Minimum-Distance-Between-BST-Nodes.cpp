/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-30 22:21:53
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
// 给我的感觉就是 每个点和它的前驱跟后继相比较
class Solution {
  public:
	int ans = INT_MAX;
	int minDiffInBST(TreeNode* root) {
		if (root->left) {
			TreeNode* pre = root->left;
			while (pre->right) pre = pre->right;
			ans = min(ans, root->val - pre->val);
			minDiffInBST(root->left)
		}
		if (root->right) {
			TreeNode* post = root->right;
			while (post->left) post = post->left;
			ans = min(ans, post->val - root->val);
			minDiffInBST(root->right)
		}
		return ans;
	}
};