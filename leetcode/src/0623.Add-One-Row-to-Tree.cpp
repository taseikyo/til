/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-28 18:07:09
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
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			TreeNode* node = new TreeNode(v, root, nullptr);
			return node;
		}
		root->left = addOneRow(root, root->left, v, d - 1);
		root->right = addOneRow(root, root->right, v, d - 1);
		return root;
	}
	TreeNode* addOneRow(TreeNode* root, TreeNode* cur, int v, int d){
		if (!cur && d == 1) {
			return new TreeNode(v);
		}
		if (!cur) {
			return nullptr;
		}
		if (d == 1) {
			TreeNode* node = new TreeNode(v);
			if (cur == root->left) {
				node->left = cur;
			} else {
				node->right = cur;
			}
			return node;
		}
		cur->left = addOneRow(cur, cur->left, v, d - 1);
		cur->right = addOneRow(cur, cur->right, v, d - 1);
		return cur;
	}
};