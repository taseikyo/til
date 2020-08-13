/**
 * @date    2020-08-13 16:30:05
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
	ListNode* removeDuplicateNodes(ListNode* head) {
		unordered_set<int> cache;
		ListNode dummy(-1);
		ListNode* tail = &dummy;
		while (head) {
			if (cache.find(head->val) == cache.end()) {
				tail->next = head;
				tail = tail->next;
				cache.insert(head->val);
			}
			head = head->next;
		}
		tail->next = nullptr;
		return dummy.next;
	}
};