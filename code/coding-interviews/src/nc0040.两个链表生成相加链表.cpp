/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:47:36
 * @link    github.com/taseikyo
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
	ListNode* addInList(ListNode* p1, ListNode* p2) {
		int carry = 0;
		ListNode dummy(-1);
		ListNode *tail = &dummy;
		while (carry || p1 || p2) {
			int x1 = p1 ? p1->val : 0;
			int x2 = p2 ? p2->val : 0;
			int v = carry + x1 + x2;
			carry = v / 10;
			v %= 10;
			tail->next = new ListNode(v);
			tail = tail->next;
			if (p1) p1 = p1->next;
			if (p2) p2 = p2->next;
		}
		return dummy.next;
	}
};