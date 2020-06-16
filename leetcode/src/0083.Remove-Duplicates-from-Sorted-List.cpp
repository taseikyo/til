/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-16 22:11:17
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
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* p, *q;
		p = head;
		q = head->next;
		while (q) {
			if (p->val == q->val) {
				p->next = q->next;
			} else {
				p = q;
			}
			q = q->next;
		}
		return head;
	}
};

class Solution {
  public:
	ListNode* deleteDuplicates(ListNode* head) {
		if ((head == nullptr) || (head->next == nullptr))
			return head;
		ListNode *track = head;
		while ( track->next ) {
			if ( track->val == track->next->val )
				track->next = track->next->next;
			else
				track = track->next;
		}
		return head;
	}
};