/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 21:25:47
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
class Solution {
  public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return foo(nums, 0, nums.size());
	}
	TreeNode* foo(vector<int>& nums, int s, int e) {
		if (s >= e) {
			return nullptr;
		}
		if (e - s == 1) {
			return new TreeNode(nums[s]);
		}
		int mid = (s + e) / 2;
		auto root = new TreeNode(nums[mid]);
		root->left = foo(nums, s, mid);
		root->right = foo(nums, mid + 1, e);
		return root;
	}
};