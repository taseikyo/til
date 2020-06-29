/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-28 17:17:58
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
	TreeNode* trimBST(TreeNode* root, int L, int R) {
		if (!root) {
			return root;
		}
		if (root->val < L) {
			root = root->right;
			return trimBST(root, L, R);
		} else if (root->val > R) {
			root = root->left;
			return trimBST(root, L, R);
		}
		trimBST(root, root->left, L, R);
		trimBST(root, root->right, L, R);
		return root;
	}
	void trimBST(TreeNode* &root, TreeNode* node, int L, int R) {
		if (!node) {
			return;
		}
		if (node->val < L) {
			root->left = node->right;
			trimBST(root, root->left, L, R);
		} else if (node->val > R) {
			root->right = node->left;
			trimBST(root, root->right, L, R);
		} else {
			trimBST(node, node->left, L, R);
			trimBST(node, node->right, L, R);
		}
	}
};

// 我在处理第三种情况的时候复杂了，下面就很好
class Solution {
  public:
	TreeNode* trimBST(TreeNode* root, int L, int R) {
		if (!root) return NULL;
		if (root->val < L) return trimBST(root->right, L, R);
		else if (root->val > R) return trimBST(root->left, L, R);
		else {
			root->left = trimBST(root->left, L, R);
			root->right = trimBST(root->right, L, R);
			return root;
		}
	}
};