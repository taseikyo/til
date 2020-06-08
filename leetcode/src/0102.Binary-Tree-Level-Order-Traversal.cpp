/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-07 17:11:12
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
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) {
			return {};
		}
		vector<vector<int>> ans;
		vector<TreeNode*> s{root};
		while (s.size()) {
			int len = s.size();
			vector<int> tmp_ans;
			for (int i = 0; i < len; ++i) {
				root = s.front();
				s.erase(s.begin());
				tmp_ans.push_back(root->val);
				if (root->left) {
					s.push_back(root->left);
				}
				if (root->right) {
					s.push_back(root->right);
				}
			}
			ans.push_back(tmp_ans);
		}
		return ans;
	}
};