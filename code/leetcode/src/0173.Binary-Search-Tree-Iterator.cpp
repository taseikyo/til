/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 20:29:55
 * @link    github.com/taseikyo
 */

// 参考 https://leetcode.com/problems/binary-search-tree-iterator/

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
class BSTIterator {
  public:
	stack<TreeNode*> stk;
	BSTIterator(TreeNode* root) {
		push_nodes(root);
	}

	/** @return the next smallest number */
	int next() {
		TreeNode* node = stk.top();
		stk.pop();
		push_nodes(node->right);
		return node->val;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !stk.empty();
	}

	void push_nodes(TreeNode* root) {
		for (; root; stk.push(root), root = root->left);
	}
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */