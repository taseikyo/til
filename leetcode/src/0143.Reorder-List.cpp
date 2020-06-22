/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 15:46:59
 * @link    github.com/taseikyo
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// 把链表分成两半，前一半正常，后一半逆序，然后分别取一构成新链表
class Solution {
  public:
	void reorderList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode *pre = nullptr, *slow, *fast;
		slow = fast = head;
		while (fast && fast->next) {
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		slow = reverse(slow);
		ListNode dummy(-1);
		auto p = &dummy;
		auto q = head;
		while (q && slow) {
			p->next = q;
			q = q->next;
			p = p->next;
			p->next = slow;
			slow = slow->next;
			p = p->next;
		}
		if (q) {
			p->next = q;
		}
		if (slow) {
			p->next = slow;
		}
	}

	ListNode* reverse(ListNode* head) {
		ListNode dummy(-1);
		auto p = &dummy;
		while (head) {
			auto tmp = head->next;
			head->next = p->next;
			p->next = head;
			head = tmp;
		}
		return dummy.next;
	}
};