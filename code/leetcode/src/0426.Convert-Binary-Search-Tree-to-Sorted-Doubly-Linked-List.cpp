/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 15:21:15
 * @link    github.com/taseikyo
 */

// 这题是上锁的，问题在之前《剑指Offer》中见过

class Solution {
  public:
	Node* treeToDoublyList(Node* root) {
		if (!root) return NULL;
		Node *head = NULL, *pre = NULL;
		inorder(root, pre, head);
		pre->right = head;
		head->left = pre;
		return head;
	}
	void inorder(Node* node, Node*& pre, Node*& head) {
		if (!node) return;
		inorder(node->left, pre, head);
		if (!head) {
			head = node;
			pre = node;
		} else {
			pre->right = node;
			node->left = pre;
			pre = node;
		}
		inorder(node->right, pre, head);
	}
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