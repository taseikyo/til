/**
 * @date    2020-08-13 17:12:24
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  public:
	bool isPalindrome(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;
		ListNode* p;
		while (fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		// 奇数，fast 不为空
		if (fast) {
			p = reverse(slow->next);
		} else {
			p = reverse(slow);
		}
		while (p) {
			if (p->val != head->val) {
				return false;
			}
			p = p->next;
			head = head->next;
		}
		return true;
	}
	ListNode* reverse(ListNode* p) {
		ListNode *pre = nullptr, *cur = p, *next;
		while (cur) {
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};