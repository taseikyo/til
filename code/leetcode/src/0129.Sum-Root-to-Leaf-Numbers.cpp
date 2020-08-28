/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-12 17:31:21
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
    int ans = 0;
    int sumNumbers(TreeNode* root) {
        if (!root) {
            return 0;
        }
        if (!root->left && !root->right) {
            ans += root->val;
        } else {
            if (root->left) {
                root->left->val += 10 * root->val;
                sumNumbers(root->left);
            }
            if (root->right) {
                root->right->val += 10 * root->val;
                sumNumbers(root->right);
            }
        }
        return ans;
    }
};