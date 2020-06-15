/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 21:34:04
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
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(-1);
		ListNode* tail = dummy;
		while (l1 && l2) {
			if (l2->val < l1->val) {
				tail->next = l2;
				l2 = l2->next;
			} else {
				tail->next = l1;
				l1 = l1->next;
			}
			tail = tail->next;
		}
		if (l1) {
			tail->next = l1;
		}
		if (l2) {
			tail->next = l2;
		}
		return dummy->next;
	}
};