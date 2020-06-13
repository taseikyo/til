/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-10 15:12:44
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&&tqId=11179&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
 */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};
class Solution {
  public:
	TreeNode* Convert(TreeNode* root) {
		if (!root) {
			return root;
		}
		if (!root->left && !root->right) {
			return root;
		}
		// 1.将左子树构造成双链表，并返回链表头节点
		TreeNode* left = Convert(root->left);
		TreeNode* p = left;
		// 2.定位至左子树双链表最后一个节点
		while (p && p->right) {
			p = p->right;
		}
		// 3.如果左子树链表不为空的话，将当前root追加到左子树链表
		if (left) {
			p->right = root;
			root->left = p;
		}
		// 4.将右子树构造成双链表，并返回链表头节点
		TreeNode* right = Convert(root->right);
		// 5.如果右子树链表不为空的话，将该链表追加到root节点之后
		if (right) {
			right->left = root;
			root->right = right;
		}
		return left ? left : root;
	}
};

// 1. 核心是中序遍历的非递归算法。
// 2. 修改当前遍历节点与前一遍历节点的指针指向。
class Solution {
  public:
	TreeNode* Convert(TreeNode* root) {
		vector<TreeNode*> v;
		TreeNode* p = root;
		// 用于保存中序遍历序列的上一节点
		TreeNode* pre = nullptr;
		// 用于设置返回的 root
		bool isFirst = true;
		while (p || v.size()) {
			while (p) {
				v.push_back(p);
				p = p->left;
			}
			p = v.back();
			v.pop_back();
			if (isFirst) {
				root = p;
				pre = p;
				isFirst = false;
			} else {
				pre->right = p;
				p->left = pre;
				pre = p;
			}
			p = p->right;
		}
		return root;
	}
};