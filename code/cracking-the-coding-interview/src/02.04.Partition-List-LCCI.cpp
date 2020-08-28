/**
 * @date    2020-08-13 16:46:38
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
	ListNode* partition(ListNode* head, int x) {
		ListNode small(-1), big(-1);
		ListNode *psmall = &small, *pbig = &big;
		while (head) {
			if (head->val < x) {
				psmall->next = head;
				psmall = psmall->next;
			} else {
				pbig->next = head;
				pbig = pbig->next;
			}
			head = head->next;
		}
		psmall->next = big.next;
		pbig->next = nullptr;
		return small.next;
	}
};