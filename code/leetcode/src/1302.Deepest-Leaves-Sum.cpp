/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 16:07:23
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
// 由于 map 是有序的，保存<深度, 叶子节点的和>，返回最后一个即可
class Solution {
  public:
	int deepestLeavesSum(TreeNode* root) {
		if (!root) {
			return 0;
		}
		if (!root->left && !root->right) {
			return root->val;
		}
		map<int, int> m;
		foo(root, m, 0);
		return m.rbegin()->second;
	}
	void foo(TreeNode* root, map<int, int> &m, int deep) {
		if (!root) {
			return;
		}
		if (!root->left && !root->right) {
			if (m.find(deep) != m.end()) {
				m[deep] += root->val;
			} else {
				m[deep] = root->val;
			}
		}
		foo(root->left, m, deep + 1);
		foo(root->right, m, deep + 1);
	}
};

// 提交区找的“快”方法，实际跑出来更慢2333，这个72ms，我那个68ms
class Solution {
  public:
	int deepestLeavesSum(TreeNode* root) {
		vector<TreeNode*> *v = new vector<TreeNode*>({root});
		while (true) {
			const int n = v->size();
			auto next_level = new vector<TreeNode*>();
			for (const auto& i : *v) {
				if (i->left) next_level->push_back(i->left);
				if (i->right) next_level->push_back(i->right);
			}
			if (next_level->size() == 0) break;
			v = next_level;
		}
		int res = 0;
		for (const auto& i : *v) res += i->val;
		return res;
	}
};