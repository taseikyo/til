/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 21:38:48
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
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> result;
		string ans;
		printNodes(root, ans, result);
		return result;
	}
	void printNodes(TreeNode* root, string& ans,
	                vector<string>& result) {
		if (root == NULL) {
			return;
		}
		ans += to_string(root->val) + "->";
		if (root->left == NULL && root->right == NULL) {
			ans.erase(ans.length() - 2, 2);
			result.push_back(ans);
		}
		string temp = ans;
		printNodes(root->left, temp, result);
		temp = ans;
		printNodes(root->right, temp, result);
	}
};