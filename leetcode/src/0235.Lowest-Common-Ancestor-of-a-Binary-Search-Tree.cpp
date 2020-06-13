/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-13 15:06:53
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

// 递归版本，看 p q 落在 root 的哪边
// 如果同一边显然上面那个是祖先
// 如果不同边就是相应的 root
class Solution {
  public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p,
	                               TreeNode* q) {
		if (!root) {
			return nullptr;
		}
		if (root == p || root == q) {
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left && right) {
			return root;
		} else if (left) {
			return left;
		}
		return right;
	}
};


// 非递归版本
// 抓住 BST 的特性
// 如果都小于 root 的值，则左子树
// 如果都大于 root 的值，则右子树
// 一大一小，那显然就是 root 了
// 
// 绝了 Submissions 中看到这个解法更快
// 实际跑的数据却比递归版本慢
// 上面 36ms，这个 44ms，所用内存一样
class Solution {
  public:
	TreeNode* lowestCommonAncestor(TreeNode* r, TreeNode* p,
	                               TreeNode* q) {
		int pv = p->val, qv  = q->val, rv;
		while (r) {
			rv = r->val;
			if (pv < rv && qv < rv)
				r = r->left;
			else if (pv > rv && qv > rv)
				r = r->right;
			else
				return r;
		}
		return nullptr;
	}
};
