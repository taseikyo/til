/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 15:00:34
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
	vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
		vector<int> v;
		vector<int> v1 = inorder(root1);
		vector<int> v2 = inorder(root2);
		if (v1.empty()) {
			return v2;
		}
		if (v2.empty()) {
			return v1;
		}
		int i = 0, j = 0;
		while (i < v1.size() || j < v2.size()) {
			if (i == v1.size()) {
				v.insert(v.end(), v2.begin()+j, v2.end());
				break;
			}
			if (j == v2.size()) {
				v.insert(v.end(), v1.begin()+i, v1.end());
				break;
			}
			if (v1[i] < v2[j]) {
				v.push_back(v1[i]);
				i++;
			} else {
				v.push_back(v2[j]);
				j++;
			}
		}
		return v;
	}

	vector<int> inorder(TreeNode* root) {
		vector<int> v1;
		vector<TreeNode*> v2;
		while ( root || v2.size() ) {
			if (root) {
				v2.push_back(root);
				root = root->left;
			} else {
				root = v2.back();
				v2.pop_back();
				v1.push_back(root->val);
				root = root->right;
			}
		}
		return v1;
	}

	void inorder(TreeNode* root, vector<int> &v) {
		if (root) {
			inorder(root->left, v);
			v.push_back(root->val);
			inorder(root->right, v);
		}
	}
};