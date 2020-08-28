/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-24 14:57:55
 * @link    github.com/taseikyo
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
  public:
	Node* connect(Node* root) {
		if (!root) return root;
		Node* parent = root;
		vector<Node*> v;
		while (parent != nullptr || !v.empty()) {
			if (!parent) {
				parent = v.back();
				v.pop_back();
				continue;
			}
			Node* cur = parent;
			while (cur) {
				Node* p = nullptr;
				if (cur->left && cur->right) {
					// 1. 左右
					cur->left->next = cur->right;
					p = cur->right;
				} else if (cur->left) {
					// 2. 左
					p = cur->left;
				} else if (cur->right) {
					// 3. 右
					p = cur->right;
				}
				// 这里有个问题是 a b c，a c 有子节点，而 b 没有子节点
				// 导致 a 的孩子链接中断
				// if (p && cur->next) {
				// 	if (cur->next->left) {
				// 		p->next = cur->next->left;
				// 	} else  if (cur->next->right) {
				// 		p->next = cur->next->right;
				// 	}
				// }
				// cur = cur->next;
				Node* tmp = cur->next;
				if (p) {
					while (tmp && !tmp->left && !tmp->right) {
						tmp = tmp->next;
					}
					if (tmp) {
						if (tmp->left) {
							p->next = tmp->left;
						} else  if (tmp->right) {
							p->next = tmp->right;
						}
					}
				}
				cur = tmp;
			}
			if (parent->right) {
				v.push_back(parent->right);
			}
			parent = parent->left;
		}
		return root;
	}
};

class Solution {
  public:
	Node* connect(Node* root) {
		if (nullptr == root)
			return nullptr;

		queue<Node*> nodes;

		nodes.push(root);
		nodes.push(nullptr);

		while (!nodes.empty()) {
			Node* tmp = nodes.front();
			nodes.pop();

			// 当 tmp 为空时，说明本层已经结束，需要为下一层添加一个结束标识
			if (nullptr == tmp) {
				if (!nodes.empty()) {
					nodes.push(nullptr);
				}
				continue;
			}

			tmp->next = nodes.front();
			if (tmp->left != nullptr) {
				nodes.push(tmp->left);
			}

			if (tmp->right != nullptr) {
				nodes.push(tmp->right);
			}
		}

		return root;
	}
};