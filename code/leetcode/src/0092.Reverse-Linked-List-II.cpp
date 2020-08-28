/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 12:29:45
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
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode* pre, *cur, *next;
		pre = dummy;
		cur = pre->next;
		while (--m) {
			pre = pre->next;
			cur = cur->next;
		}
		n -= m;
		while (n--) {
			next = cur->next;
			cur->next = next->next;
			next->next = pre->next;
			pre->next = next;
		}
		return dummy->next;
	}
};