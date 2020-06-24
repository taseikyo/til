/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 13:40:20
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
// 类似 #109 直接分治就行，中间为根，左右分别递归
class Solution {
  public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		if (nums.empty()) {
			return nullptr;
		}
		if (nums.size() == 1) {
			return new TreeNode(nums[0]);
		}
		TreeNode* root;
		foo(nums, root, 0, nums.size());
		return root;
	}
	void foo(vector<int>& nums, TreeNode* &curr, int begin, int end) {
		if (begin < 0 or end < 0 or begin >= end) {
			return;
		}

		int mid = (begin + end) / 2;
		curr = new TreeNode(nums[mid]);
		foo(nums, curr->left, begin, mid);
		foo(nums, curr->right, mid + 1, end);
	}
};