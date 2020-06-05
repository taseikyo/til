/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-05 15:40:29
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e?tpId=13&&tqId=11210&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
 */

struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};


// 如果节点有右孩子，那么下一个节点就是该孩子的最左孩子
// 否则如果该节点是他父节点的左孩子，下一个就是他的父节点
// 不然得往上看

class Solution {
  public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode) {
		if (not pNode) {
			return NULL;
		}
		if (pNode->right) {
			pNode = pNode->right;
			while (pNode->left) {
				pNode = pNode->left;
			}
			return pNode;
		}
		// 根节点的 next 为空
		while (pNode->next) {
			TreeLinkNode *proot = pNode->next;
			if (proot->left == pNode)
				return proot;
			pNode = pNode->next;
		}
		return NULL;
	}
};