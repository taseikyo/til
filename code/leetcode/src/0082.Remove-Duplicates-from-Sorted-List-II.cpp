/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 12:20:59
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
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode* pre, * cur;
		pre = dummy;
		cur = pre->next;
		while (cur && cur->next) {
			if (cur->val == cur->next->val) {
				while (cur->next && (cur->val == cur->next->val)) {
					cur = cur->next;
				}
				pre->next = cur->next;
				cur = cur->next;
			} else {
				pre = cur;
				cur = cur->next;
			}
		}
		return dummy->next;
	}
};