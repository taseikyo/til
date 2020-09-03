/**
 * @date    2020-09-03 19:32:30
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
	bool hasCycle(ListNode *head) {
		if (!head || !head->next) {
			return false;
		}
		ListNode *slow, *fast;
		slow = fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				return true;
			}
		}
		return false;
	}
};