/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 14:05:00
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
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		if (!root) {
			return {};
		}
		vector<vector<int>> ans;
		vector<int> v;
		foo(root, sum, ans, v);
		return ans;
	}
	void foo(TreeNode* root, int sum, vector<vector<int>> &ans,
	         vector<int> &v) {
		if (!root) {
			return;
		}
		v.push_back(root->val);
		sum -= root->val;
		if (sum == 0 && !root->left && !root->right) {
			ans.push_back(v);
			return;
		}
		if (root->left) {
			foo(root->left, sum, ans, v);
			v.pop_back();
		}
		if (root->right) {
			foo(root->right, sum, ans, v);
			v.pop_back();
		}
	}
};