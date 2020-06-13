/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 21:59:55
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
		if (!root) {
			return root;
		}
		foo(root->left, root->right);
		return root;
	}
	void foo(Node* &left, Node* &right) {
		if (!left) {
			return;
		}
		left->next = right;
		right->next = NULL;
		if (left->left) {
			foo(left->left, left->right);
			foo(left->right, right->left);
			foo(right->left, right->right);
		} else {
			return;
		}
	}
};
// 上面写的递归太慢了，看了下解答的迭代解法，太强了
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return root;
        Node* parent = root;
        while (parent->left){
            Node* cur = parent;
            while (cur){
                cur->left->next = cur->right;
                // 这个 if 就是把跨节点的两个子节点连起来了
                if (cur->next)
                    cur->right->next = cur->next->left;
                cur = cur->next;
            }
            parent = parent->left;
        }
        return root;
    }
};