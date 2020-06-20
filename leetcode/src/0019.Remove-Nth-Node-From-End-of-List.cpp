/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 12:00:21
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
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* fast, *slow;
		slow = fast = head;
		while (n--) {
			fast = fast->next;
		}
		// 正好 n 个，倒数第 n ，返回第二个
		if (!fast) {
			return head->next;
		}
		while (fast->next) {
			fast = fast->next;
			slow = slow->next;
		}
		slow->next = slow->next->next;
		return head;
	}
};