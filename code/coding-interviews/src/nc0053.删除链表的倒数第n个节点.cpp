/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:21:56
 * @link    github.com/taseikyo
 */

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
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
	 * @param head ListNode类
	 * @param n int整型
	 * @return ListNode类
	 */
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode * result = new ListNode(1);
		result->next = head;
		ListNode * p1 = head;
		ListNode * p2 = result;
		for (int i = 0; i < n; i++) {
			p1 = p1->next;
		}
		while (p1) {
			p2 = p2->next;
			p1 = p1->next;
		}
		p2->next = p2->next->next;
		return result->next;
	}
};