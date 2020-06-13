/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-10 20:12:26
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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<TreeNode*> v;
		vector<vector<int>> ans;
		vector<int> tmp_ans;
		if (!root) {
			return ans;
		}
		v.push_back(root);
		// true: left->right
		bool direction = true;
		while (v.size()) {
			int len = v.size();
			tmp_ans.clear();
			for (int i = 0; i < len; ++i) {
				root = v[0];
				if (root->left) {
					v.push_back(root->left);
				}
				if (root->right) {
					v.push_back(root->right);
				}
				tmp_ans.push_back(root->val);
				v.erase(v.begin());
			}
			if (!direction) {
				reverse(tmp_ans.begin(), tmp_ans.end());
			}
			ans.push_back(tmp_ans);
			direction = !direction;
		}
		return ans;
	}
};