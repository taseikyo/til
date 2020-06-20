/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 13:20:38
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
	ListNode* swapPairs(ListNode* head) {
		// 这题跟 25 题类似，相当于就是 k = 2 的情况
		if (!head || !head->next) {
			return head;
		}
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode* pre, * cur, *next;
		pre = dummy;
		cur = pre->next;
		while (cur && cur->next) {
			next = cur->next;
			cur->next = next->next;
			next->next = pre->next;
			pre->next = next;
			pre = cur;
			cur = cur->next;
		}
		return dummy->next;
	}
};