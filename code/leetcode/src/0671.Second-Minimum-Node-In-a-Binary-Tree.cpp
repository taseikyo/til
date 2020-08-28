/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 15:28:58
 * @link    github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 错误方法，理解错了，因为 root=min(left, right) 没错
// 但是可能 left->left 比 right更小啊
// [1,1,3,1,1,3,4,3,1,1,1,3,8,4,8,3,3,1,6,2,1] 34/35
class Solution {
  public:
	int findSecondMinimumValue(TreeNode* root) {
		int x1 = INT_MAX, x2 = INT_MAX;
		if (!root) {
			return -1;
		}
		if (root->left) {
			x1 = root->left->val;
			x2 = root->right->val;
			if (x1 != x2) {
				return max(x1, x2);
			}
		}
		return -1;
	}
};
// 相当于还是得遍历一遍，这样也有问题
// [2,2,2147483647] 34/35 直接甩你一个 INT_MAX
// 所以需要把 x1 x2 设置为 uint_max
class Solution {
  public:
	int findSecondMinimumValue(TreeNode* root) {
		unsigned x1 = UINT_MAX, x2 = UINT_MAX;
		foo(root, x1, x2);
		if (x2 == INT_MAX) {
			return -1;
		}
		return x2;
	}
	void foo(TreeNode* root, int &x1, int &x2) {
		if (root) {
			if (root->val <= x1) {
				x1 = root->val;
			} else if (root->val < x2) {
				x2 = root->val;
			}
			foo(root->left, x1, x2);
			foo(root->right, x1, x2);
		}
	}
};