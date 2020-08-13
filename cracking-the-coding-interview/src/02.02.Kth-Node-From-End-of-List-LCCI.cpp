/**
 * @date    2020-08-13 16:39:17
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
	int kthToLast(ListNode* head, int k) {
		ListNode* fast = head;
		ListNode* slow = head;
		while (k--) {
			fast = fast->next;
		}
		while (fast) {
			fast = fast->next;
			slow = slow->next;
		}
		return slow->val;
	}
};