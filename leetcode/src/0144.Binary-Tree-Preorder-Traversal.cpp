/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 16:15:59
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
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> v;
		vector<TreeNode*> s;
		while (root || s.size()) {
			if (root) {
				s.push_back(root);
				v.push_back(root->val);
				root = root->left;
			} else {
				root = s.back();
				s.pop_back();
				root = root->right;
			}
		}
		return v;
	}
};