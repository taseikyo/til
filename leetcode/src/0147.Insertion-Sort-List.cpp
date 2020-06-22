/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 15:58:26
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
	ListNode* insertionSortList(ListNode* head) {
		// if list is empty or has only one node
		if (!head || !head->next)
			return head;

		// make an empty list, it will store nodes in sorted order
		ListNode* newList = NULL;

		ListNode* current = head;

		while (current) {

			// store current's next in a variable
			ListNode* next = current->next;

			// insert this node is its correct position in the new list.
			if (newList == NULL || newList->val >= current->val) {
				ListNode* temp = newList;
				newList = current;
				newList->next = temp;
			} else {
				ListNode* temp = newList;
				while (temp && temp->next && temp->next->val <= current->val) {
					temp = temp->next;
				}
				ListNode* t = temp->next;
				temp->next = current;
				temp->next->next = t;
			}
			// go the the next node
			current = next;
		}
		return newList;
	}
};