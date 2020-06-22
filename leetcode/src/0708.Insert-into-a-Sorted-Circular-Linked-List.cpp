/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 15:26:39
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	Node* insert(Node* head, int insertVal) {
		if (!head) {
			head = new Node(insertVal, NULL);
			head->next = head;
			return head;
		}
		Node *pre = head, *cur = pre->next;
		while (cur != head) {
			if (pre->val <= insertVal && cur->val >= insertVal) break;
			if (pre->val > cur->val && (pre->val <= insertVal
			                            || cur->val >= insertVal)) break;
			pre = cur;
			cur = cur->next;
		}
		auto node = new Node(insertVal);
		pre->next = node;
		node->next = cur;
		return head;
	}
};