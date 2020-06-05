/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 15:11:24
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/564f4c26aa584921bc75623e48ca3011?tpId=13&&tqId=11171&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 操作给定的二叉树，将其变换为源二叉树的镜像。
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
	void Mirror(TreeNode *pRoot) {
		if (pRoot) {
			TreeNode *tmp = pRoot->left;
			pRoot->left = pRoot->right;
			pRoot->right = tmp;
			if (pRoot->left) {
				Mirror(pRoot->left);
			}
			if (pRoot->right) {
				Mirror(pRoot->right);
			}
		}
	}
};