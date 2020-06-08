/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-07 17:48:33
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
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
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
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

class Solution {
  public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		int depth = _depth(root);
		vector<vector<int>> res(depth, vector<int> {});

		_levelOrder(root, res, depth - 1);

		return res;
	}

	int _depth(TreeNode* root) {
		if (!root) {
			return 0;
		}
		return max(_depth(root->left), _depth(root->right)) + 1;
	}

	void _levelOrder(TreeNode* root, vector<vector<int>> &res,
	                 int depth) {
		if (!root) {
			return;
		}
		res[depth].push_back(root->val);
		_levelOrder(root->left, res, depth - 1);
		_levelOrder(root->right, res, depth - 1);
	}
};