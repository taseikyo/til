/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 14:21:55
 * @link    github.com/taseikyo
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
  public:
	Node* copyRandomList(Node* head) {
		if (!head) {
			return NULL;
		}
		// 复制节点
		Node* cur = head;
		while (cur) {
			Node* node = new Node(cur->val);
			node->next = cur->next;
			cur->next = node;
			cur = node->next;
		}
		// 复制 random
		cur = head;
		while (cur) {
			if (cur->random) {
				cur->next->random = cur->random->next;
			}
			cur = cur->next->next;
		}
		// 断链
		cur = head;
		Node* ret = head->next;
		while (cur && cur->next) {
			Node* tmp = cur->next;
			cur->next = cur->next->next;
			cur = tmp;
		}
		return ret;
	}
};