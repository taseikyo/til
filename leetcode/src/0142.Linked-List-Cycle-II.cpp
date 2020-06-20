/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 22:08:01
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
		if (!head || !head->next) {
			return NULL;
		}
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow) {
				break;
			}
		}
		if (slow == fast) {
			slow = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
		return NULL;
	}
};