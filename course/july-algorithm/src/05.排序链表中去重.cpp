/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 22:37:23
 * @link    github.com/taseikyo
 */

class Solution {
  public: ListNode *deleteDuplicates(ListNode *head) {
		if (head == nullptr)
			return nullptr;
		for (ListNode *prev = head, *cur = head->next; cur;
		        cur = cur->next) {
			if (prev->val == cur->val) {
				prev->next = cur->next;
				delete cur;
			} else {
				prev = cur;
			}
		}
		return head;
	}
};