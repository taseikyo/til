/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-01 16:15:16
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/ef068f602dde4d28aab2b210e859150a?tpId=13&tqId=11215&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数值大小顺序第三小结点的值为4。
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
	TreeNode* KthNode(TreeNode* pRoot, int k) {
		return preorder(pRoot, k);
	}

	TreeNode* preorder(TreeNode* pRoot, int k) {
		vector<TreeNode*> s;
		if (pRoot) {
			while (s.size() || pRoot) {
				if (pRoot) {
					s.push_back(pRoot);
					pRoot = pRoot->left;
				} else {
					pRoot = s.back();
					s.pop_back();
					k--;
					if (k == 0) {
						return pRoot;
					}
					pRoot = pRoot->right;
				}
			}
		}
		return NULL;
	}
};