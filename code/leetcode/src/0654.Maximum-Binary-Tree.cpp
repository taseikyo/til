/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 16:26:34
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
	TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
		if (nums.empty()) {
			return nullptr;
		} else if (nums.size() == 1) {
			return new  TreeNode(nums[0]);
		}
		return foo(nums, 0, nums.size());
	}
	TreeNode* foo(vector<int>& nums, int start, int end) {
		if (end <= start || start < 0 || end < 0) {
			return nullptr;
		}
		if (end - start == 1) {
			return new TreeNode(nums[start]);
		}
		int max = nums[start];
		int maxId = start;
		for (int i = start; i < end; ++i) {
			if (max < nums[i]) {
				max = nums[i];
				maxId = i;
			}
		}
		TreeNode*root = new TreeNode(nums[maxId]);
		if (maxId == start) {
			root->right = foo(nums, maxId + 1, end);
		} else if (maxId == end - 1) {
			root->left = foo(nums, start, maxId);
		} else {
			root->left = foo(nums, start, maxId);
			root->right = foo(nums, maxId + 1, end);
		}
		return root;
	}
};