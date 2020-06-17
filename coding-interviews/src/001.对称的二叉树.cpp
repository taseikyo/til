/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-01 15:58:21
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/ff05d44dfdb04e1d83bdbdab320efbcb?tpId=13&tqId=11211&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
 */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};

class Solution {
  public:
	bool isSymmetrical(TreeNode* pRoot) {
		if (!pRoot) {
			return true;
		}
		return isSymmetrical(pRoot->left, pRoot->right);

	}

	bool isSymmetrical(TreeNode* left, TreeNode* right) {
		if (left && right) {
			return (left->val == right->val)
			       && isSymmetrical(left->left, right->right)
			       && isSymmetrical(left->right, right->left);
		} else if (left || right) {
			return false;
		}
		return true;
	}
};