/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 22:10:28
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

// 删除分三种：
// 1. 是叶节点，直接删除
// 2. 只有一边子树，把子树链到父节点
// 3. 有左右，比较麻烦，找到后继，把后继的值复制到删除点，然后删除后继
class Solution {
  public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		TreeNode* node = findNode(root, key);
		if (!node) {
			return root;
		}
		TreeNode* dummy = new TreeNode(INT_MAX, root, nullptr);
		TreeNode* parent = findParent(dummy, node);
		cout<<node->val<<" "<<parent->val;
		if (!node->left && !node->right) {
			// 1. 叶节点
			if (parent->left == node) {
				parent->left = nullptr;
			} else {
				parent->right = nullptr;
			}
		} else if (node->left && node->right) {
			// 3. 双边节点
			TreeNode* pre_after = node;
			TreeNode* after = node->right;
			while (after->left) {
				pre_after  = after;
				after = after->left;
			}
			node->val = after->val;
			if (pre_after->left == after) {
				pre_after->left = after->right;
			} else {
				pre_after->right = after->right;
			}
		} else {
			// 2. 一边子节点
			bool left = false;
			if (node == parent->left) {
				left = true;
			}
			if (node->left) {
				if (left) {
					parent->left = node->left;
				} else {
					parent->right = node->left;
				}
			} else {
				if (node == root) {
					parent->left = node->right;
				} else {
					if (left) {
						parent->left = node->right;
					} else {
						parent->right = node->right;
					}
				}
			}
		}
		return dummy->left;
	}
	TreeNode* findNode(TreeNode* root, int key) {
		if (!root) {
			return nullptr;
		}
		if (root->val == key) {
			return root;
		} else if (root->val > key) {
			return findNode(root->left, key);
		} else {
			return findNode(root->right, key);
		}
	}
	TreeNode* findParent(TreeNode* root, TreeNode* node) {
		if (!root) {
			return nullptr;
		}
		if (root->left == node || root->right == node) {
			return root;
		}
		if (node->val > root->val) {
			return findParent(root->right, node);
		}
		return findParent(root->left, node);
	}
};