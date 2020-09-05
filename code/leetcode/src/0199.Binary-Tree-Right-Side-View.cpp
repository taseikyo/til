/**
 * @date    2020-09-01 09:27:23
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 层序遍历，取最右的数据
class Solution {
  public:
	vector<int> rightSideView(TreeNode* root) {
		if (!root) {
			return {};
		}
		vector<TreeNode*> nodes{root};
		vector<int> ans;
		while (nodes.size()) {
			int n = nodes.size();
			ans.push_back(nodes[n - 1]->val);
			while (n--) {
				auto node = nodes.front();
				nodes.erase(nodes.begin());
				if (node->left) {
					nodes.push_back(node->left);
				}
				if (node->right) {
					nodes.push_back(node->right);
				}
			}
		}
		return ans;
	}
};