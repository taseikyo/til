/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 16:39:41
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
class FindElements {
  public:
	FindElements(TreeNode* r) {
		populate(r, 0);
	}

	bool find(int target) {
		return s.count(target);
	}

	void populate(TreeNode* root, int v) {
		if (!root) return;
		root->val = v;
		s.insert(v);
		if (root->left) populate(root->left, 2 * v + 1);
		if (root->right) populate(root->right, 2 * v + 2);
	}
	std::unordered_set<int> s;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */