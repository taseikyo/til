/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-16 22:44:24
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
class Solution {
  public:
	ListNode* oddEvenList(ListNode* head) {
		if (!head || !head->next || !head->next->next) {
			return head;
		}
		ListNode* a = head;
		ListNode* b = head->next;
		ListNode*p = b->next;
		while (p) {
			a->next = p;
			b->next = p->next;

			if (p->next) {
				p = p->next;
			}
			p = p->next;
			a = a->next;
			b = b->next;
		}
		a->next = b;
		return head;
	}
};


// 我上面太复杂，从提交区找了一份
class Solution {
  public:
	ListNode* oddEvenList(ListNode* head) {
		if (!head or !head->next) {
			return head;
		}
		ListNode *odd = head , *even = head->next;
		ListNode  *s_o = odd , *s_e = even;
		while (even and even->next) {
			odd->next = odd->next->next;
			even->next = even->next->next;
			odd = odd->next;
			even = even->next;
		}
		odd->next = s_e;
		return s_o;
	}
};