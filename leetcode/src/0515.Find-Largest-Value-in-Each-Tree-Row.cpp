/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 22:13:54
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
// 最简单的层序遍历的时候获取最大值，但是速度极慢 6.58% 2333
class Solution {
  public:
	vector<int> largestValues(TreeNode* root) {
		if (!root) {
			return {};
		}
		vector<int> ans;
		vector<TreeNode*> s{root};
		while (s.size()) {
			int len = s.size();
			int max = INT_MIN;
			for (int i = 0; i < len; ++i) {
				root = s.front();
				s.erase(s.begin());
				if (max < root->val) {
					max = root->val;
				}
				if (root->left) {
					s.push_back(root->left);
				}
				if (root->right) {
					s.push_back(root->right);
				}
			}
			ans.push_back(max);
		}
		return ans;
	}
};

// 这个方法挺巧妙的
class Solution {
  public:
	vector<int> largestValues(TreeNode* root) {
		vector<int> maxs;
		find(root, 0, maxs);
		return maxs;
	}

  private:
	void find(TreeNode* node, int row, vector<int>& maxs) {
		if (!node) {
			return;
		}

		if (row >= maxs.size()) {
			maxs.push_back(node->val);
		} else {
			maxs[row] = max(maxs[row], node->val);
		}

		find(node->left, row + 1, maxs);
		find(node->right, row + 1, maxs);
	}
};