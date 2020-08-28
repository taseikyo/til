/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 21:22:39
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
	ListNode* sortList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode*slow, *fast;
		slow = head;
		fast = head->next;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = slow->next;
		slow->next = nullptr;
		ListNode*left = sortList(head);
		ListNode*right = sortList(fast);
		return merge(left, right);
	}

	ListNode* merge(ListNode* left, ListNode* right) {
		ListNode dummy(-1);
		auto p = &dummy;
		while (left && right) {
			if (left->val < right->val) {
				p->next = left;
				left = left->next;
			} else {
				p->next = right;
				right = right->next;
			}
			p = p->next;
		}
		if (left) {
			p->next = left;
		}
		if (right) {
			p->next = right;
		}
		return dummy.next;
	}
};