/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 21:49:31
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
	ListNode* reverseList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* p, *c, *n;
		p = nullptr;
		c = head;
		while (c) {
			n = c->next;
			c->next = p;
			p = c;
			c = n;
		}
		return p;
	}
};