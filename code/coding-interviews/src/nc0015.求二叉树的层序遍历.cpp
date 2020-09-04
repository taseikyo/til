/**
 * @date    2020-09-04 15:31:15
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
  public:
	/**
	 *
	 * @param root TreeNode类
	 * @return int整型vector<vector<>>
	 */
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> ans;
		if (!root) {
			return {};
		}
		queue<TreeNode*> q;
		q.push(root);
		while (q.size()) {
			int n = q.size();
			vector<int> tmp;
			while (n--) {
				auto node = q.front();
				q.pop();
				if (node->left) {
					q.push(node->left);
				}
				if (node->right) {
					q.push(node->right);
				}
				tmp.push_back(node->val);
			}
			ans.push_back(tmp);
		}
		return ans;
	}
};