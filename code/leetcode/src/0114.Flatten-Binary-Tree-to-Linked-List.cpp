/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 14:18:36
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
// 参考先序遍历，保存右节点，然后修改右指针
// 方法二：先序遍历，然后建立节点
class Solution {
  public:
	void flatten(TreeNode* root) {
		vector<TreeNode*> v;
		TreeNode* p = root;
		TreeNode* pre = nullptr;
		while (p || v.size()) {
			while (p) {
				if (p->right) {
					v.push_back(p->right);
				}
				p->right = p->left;
				p->left = nullptr;
				pre = p;
				p = p->right;
			}
			if (v.size()) {
				p = v.back();
				v.pop_back();
				pre->right = p;
			}
		}
	}
};