/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 21:43:52
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
	void check(TreeNode* root, int sum, bool &ans) {
		if (!root->left and !root->right) {
			sum -= root->val;
			if (sum == 0) {
				ans = true;
			}
			return;
		}
		if (root->left) check(root->left, sum - root->val, ans);
		if (root->right) check(root->right, sum - root->val, ans);
		return;
	}
	bool hasPathSum(TreeNode* root, int sum) {
		if (!root) {
			return false;
		}
		bool ans = false;
		check(root, sum, ans);
		return ans;

	}
};
// 这个方法很有趣，从上往下把值加起来，看最后叶子节点的值是否等于 sum
class Solution {
  public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == NULL) {
			return false;
		}
		queue<TreeNode*> Q;
		TreeNode* temp = root;
		Q.push(temp);

		while (!Q.empty()) {
			temp = Q.front();
			int num = Q.front()->val;
			if (temp->left != NULL) {
				temp->left->val += num;
				Q.push(temp->left);
			}
			if (temp->right != NULL) {
				temp->right->val += num;
				Q.push(temp->right);
			}
			if (temp->left == NULL && temp->right == NULL && temp->val == sum) {
				return true;
			}
			Q.pop();
		}
		return false;

	}
};