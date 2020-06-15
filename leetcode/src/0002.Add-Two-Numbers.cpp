/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 21:16:29
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
// 这个方法的空间利用率太低（0），都是新建节点
class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(-1);
		ListNode* tail = dummy;
		int carry = 0;
		while (l1 || l2) {
			int v1 = l1 ? l1->val : 0;
			int v2 = l2 ? l2->val : 0;
			int sum = v1 + v2 + carry;
			carry = sum / 10;
			sum %= 10;
			tail->next = new ListNode(sum);
			tail = tail->next;
			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}
		if (carry)  tail->next = new ListNode(1);
		return dummy->next;
	}
};

class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int carry = 0;
		ListNode* head = l1;
		ListNode* prev;
		while (l1 && l2) {
			l1->val += l2->val + carry;
			if (l1->val > 9) {
				l1->val -= 10;
				carry = 1;
			} else {
				carry = 0;
			}
			prev = l1;
			l1 = l1->next;
			l2 = l2->next;
		}
		if (l2) {
			prev->next = l2;
			l1 = l2;
		}

		while (l1) {
			if (!carry) {
				break;
			}
			l1->val += carry;
			if (l1->val > 9) {
				l1->val -= 10;
				carry = 1;
			} else {
				carry = 0;
			}
			prev = l1;
			l1 = l1->next;
		}

		if (carry) {
			prev->next = new ListNode(1);
		}

		return head;
	}
};