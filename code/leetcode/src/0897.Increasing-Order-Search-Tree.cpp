/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 16:19:40
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
	TreeNode* increasingBST(TreeNode* root) {
		TreeNode* cur = root;
		TreeNode* pre;
		vector<TreeNode*> v;
		bool first = true;
		while (cur || v.size()) {
			while (cur) {
				v.push_back(cur);
				cur = cur->left;
			}
			cur = v.back();
			v.pop_back();
			if (first) {
				first = false;
				root = cur;
				pre = cur;
			} else {
				pre->right = cur;
				cur->left = nullptr;
				pre = cur;
			}
			cur = cur->right;
		}
		return root;
	}
};