/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-06 17:10:23
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
// 贪心，放在叶子的父节点
// 返回 0：叶子
// 		1：叶子的父节点，放置
// 		2：被监控了
// 对于每个节点：
// 		如果他有孩子，该孩子是叶节点(node 0)，则放置
// 		如果他有孩子，该孩子是叶节点的父节点(node 1)，则不用
class Solution {
  public:
	int res = 0;
	int minCameraCover(TreeNode* root) {
		return (dfs(root) < 1 ? 1 : 0) + res;
	}

	void dfs(TreeNode* root, TreeNode* parent = nullptr) {
		if (!root) return 2;
		int left = dfs(root->left), right = dfs(root->right);
		if (left == 0 || right == 0) {
			res++;
			return 1;
		}
		return left == 1 || right == 1 ? 2 : 0;
	}
};