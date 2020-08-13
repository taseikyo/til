/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-13 19:42:03
 * @link    github.com/taseikyo
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
	ListNode *detectCycle(ListNode *head) {
		ListNode *fast, *slow;
		fast = slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow) {
				fast = head;
				while(fast != slow) {
					fast = fast->next;
					slow = slow->next;
				}
				return slow;
			}
		}
		return nullptr;
	}
};