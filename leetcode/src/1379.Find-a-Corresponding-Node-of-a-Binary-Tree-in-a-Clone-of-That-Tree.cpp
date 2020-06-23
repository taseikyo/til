/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 16:21:46
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
// 这个题目真弱智
class Solution {
  public:
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned,
	                        TreeNode* target) {
		if (!original) {
			return original;
		}
		if (original == target) {
			return cloned;
		}
		TreeNode* ans = getTargetCopy(original->left, cloned->left, target);
		if (ans) {
			return ans;
		}
		ans = getTargetCopy(original->right, cloned->right, target);
		return ans;
	}
};