/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 12:46:25
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
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode* pre, * cur, *next;
		pre = dummy;
		cur = pre->next;
		int n = length(head);
		int times = n/k;
		while (cur && cur->next && times--) {
			for (int i = 1; i < k && cur->next; ++i) {
				next = cur->next;
				cur->next = next->next;
				next->next = pre->next;
				pre->next = next;
			}
			pre = cur;
			cur = cur->next;
		}
		return dummy->next;
	}
	int length(ListNode* head) {
		int ans = 0;
		while(head){
			head=head->next;
			ans++;
		}
		return ans;
	}
};