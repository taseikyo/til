/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-12 17:38:14
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
// 递归就很容易
class Solution {
  public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		foo(root, ans);
		return ans;
	}
	void foo(TreeNode* root, vector<int> &v) {
		if (root) {
			foo(root->left, v);
			foo(root->right, v);
			v.push_back(root->val);
		}
	}
};

// 非递归就很麻烦
class Solution {
  public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		vector<TreeNode*> s1;
		vector<TreeNode*> s2;
		if (root) {
			s1.push_back(root);
			while (s1.size()) {
				root = s1.back();
				s1.pop_back();
				s2.push_back(root);
				if (root->left) {
					s1.push_back(root->left);
				}
				if (root->right) {
					s1.push_back(root->right);
				}
			}
			while (s2.size()) {
				root = s2.back();
				s2.pop_back();
				ans.push_back(root->val);
			}
		}
		return ans;
	}
};
