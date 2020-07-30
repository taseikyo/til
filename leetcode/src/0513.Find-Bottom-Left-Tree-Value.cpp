/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-30 21:41:34
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
// bfs 每次保存第一个数
class Solution {
  public:
	int findBottomLeftValue(TreeNode* root) {
		queue<TreeNode*> q;
		int ans;
		q.push(root);
		while (q.size()) {
			int size = q.size();
			int first = 0;
			for (int i = 0; i < size; ++i) {
				TreeNode* p = q.front();
				q.pop();
				if (first == 0) {
					ans = p->val;
					++first;
				}
				if (p->left) {
					q.push(p->left);
				}
				if (p->right) {
					q.push(p->right);
				}
			}
		}
		return ans;
	}
};
