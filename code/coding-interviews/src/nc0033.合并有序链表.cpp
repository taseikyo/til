/**
 * @date    2020-09-03 20:17:52
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
  public:
	/**
	 *
	 * @param p1 ListNode类
	 * @param p2 ListNode类
	 * @return ListNode类
	 */
	ListNode* mergeTwoLists(ListNode* p1, ListNode* p2) {
		ListNode* dummy = new ListNode(-1);
		ListNode* tail = dummy;
		while (p1 && p2) {
			if (p1->val < p2->val) {
				tail->next = p1;
				p1 = p1->next;
			} else {
				tail->next = p2;
				p2 = p2->next;
			}
			tail = tail->next;
		}
		if (p1) {
			tail->next = p1;
		}
		if (p2) {
			tail->next = p2;
		}
		return dummy->next;
	}
};