/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-06 14:47:45
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
	TreeNode* bstFromPreorder(vector<int>& preorder) {
		return bstFromPreorder(preorder, 0, preorder.size());
	}

	TreeNode* bstFromPreorder(vector<int>& preorder, int begin,
	                          int end) {
		if (end <= begin) {
			return nullptr;
		}
		TreeNode* root = new TreeNode(preorder[begin]);
		int idx = binary_search(preorder, begin + 1, end, root -> val);
		root -> left = bstFromPreorder(preorder, begin + 1, idx);
		root -> right = bstFromPreorder(preorder, idx, end);
		return root;
	}
	int binary_search(vector<int>& preorder, int begin, int end,
	                  int target) {
		if (end <= begin || target > preorder[end - 1]) {
			return end;
		}
		if (target < preorder[begin]) {
			return begin;
		}
		int mid = (end + begin) / 2;
		while (end > begin) {
			if (preorder[mid] < target) {
				begin = mid + 1;
			} else {
				end = mid;
			}
			mid = (begin + end) / 2;
		}
		return begin;
	}
};