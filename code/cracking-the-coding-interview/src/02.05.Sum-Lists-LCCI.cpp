/**
 * @date    2020-08-13 16:56:02
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
// 简单方法 将链表转化为 数字 然后再转化为链表
class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int x = foo(l1);
		int y = foo(l2);
		x += y;
		ListNode dummy(-1);
		ListNode *tail = &dummy;
		while (x) {
			tail->next = new ListNode(x % 10);
			tail = tail->next;
			x /= 10;
		}
		return dummy.next;
	}
	int foo(ListNode* &l) {
		int ans = 0;
		while (l) {
			ans = ans * 10 + l->val;
			l = l->next;
		}
		return ans;
	}
};

class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummy(-1);
		ListNode *tail = &dummy;
		int carry = 0;
		while (l1 || l2) {
			int x = l1 ? l1->val : 0;
			x += l2 ? l2->val : 0 + carry;
			if (x >= 10) {
				carry = 1;
				x /= 10;
			} else {
				carry = 0;
			}
			tail->next = new ListNode(x % 10);
			tail = tail->next;
			l1 = l1 ? l1->next : nullptr;
			l2 = l2 ? l2->next : nullptr;
		}
		if (carry) {
			tail->next = new ListNode(carry);
		}
		return dummy.next;
	}
};