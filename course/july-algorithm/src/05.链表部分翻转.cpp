/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 22:25:41
 * @link    github.com/taseikyo
 */

class Solution {
	public：ListNode*reverseBetween(ListNode*head, int m, int n) {
		ListNode dummy(-1);
		dummy.next = head;
		ListNode*prev = &dummy;
		for (int i = 0; i < m - 1; ++i)
			prev = prev->next;

		ListNode* const head2 = prev;
		prev = head2->next;
		ListNode* cur = prev->next;
		for (int i = m; i < n; ++i) {
			prev->next = cur->next;
			cur->next = head2->next;
			head2->next = cur; //头插法
			cur = prev->next;
		}
		return dummy.next;
	}
};