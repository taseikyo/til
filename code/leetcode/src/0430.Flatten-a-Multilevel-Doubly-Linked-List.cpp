/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 17:15:51
 * @link    github.com/taseikyo
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

// 最简单的方法，先遍历一遍拿到所有值，然后重建链表
class Solution {
  public:
	Node* flatten(Node* head) {
		if (!head) {
			return nullptr;
		}
		vector<int> v;
		foo(head, v);
		Node* root = new Node(v[0]);
		Node* pre = root;
		for (int i = 1; i < v.size(); ++i) {
			Node* node = new Node(v[i]);
			pre->next = node;
			node->prev = pre;
			pre = node;
		}
		return root;
	}
	void foo(Node* head, vector<int> &v) {
		if (!head) {
			return;
		}
		v.push_back(head->val);
		foo(head->child, v);
		foo(head->next, v);
	}
};

class Solution {
  public:
	Node* flatten(Node* head) {
		if (!head) {
			return nullptr;
		}
		vector<Node*> v;
		Node *pre = nullptr;
		Node *cur = head;
		while (cur || v.size()) {
			if (cur) {
				if (pre) {
					pre->child = nullptr;
					pre->next = cur;
					cur->prev = pre;
				}
				pre = cur;
				if (cur->child) {
					if (cur->next) {
						v.push_back(cur->next);
					}
					cur = cur->child;
				} else {
					cur = cur->next;
				}
			} else if (v.size()) {
				cur = v.back();
				v.pop_back();
			}
		}
		return head;
	}
};

// 提交区的改进版，比我又臭又长的代码简洁多了
// 有意思的是跑的时间内存一样
class Solution {
  public:
	Node* flatten(Node* head) {
		if (!head) return head;
		Node* res = head;
		std::stack<Node*> s;
		while (head || !s.empty()) {
			if (head->child) {
				if (head->next) s.push(head->next);
				head->child->prev = head;
				head->next = head->child;
				head->child = NULL;
			} else if ( !head->next) {
				if (!s.empty()) {
					Node* next = s.top();
					s.pop();
					head->next = next;
					next->prev = head;
				}
			}
			head = head->next;
		}
		return res;
	}
};