/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 14:32:21
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
	ListNode* removeElements(ListNode* head, int val) {
		ListNode dummy(-1);
		dummy.next = head;
		ListNode* pre = &dummy;
		ListNode* cur = head;
		while (cur) {
			if (cur->val == val) {
				cur = cur->next;
			} else {
				pre->next = cur;
				pre = cur;
				cur = cur->next;
			}
		}
		pre->next = cur;
		return dummy.next;
	}
};