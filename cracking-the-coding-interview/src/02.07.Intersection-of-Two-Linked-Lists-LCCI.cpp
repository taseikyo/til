/**
 * @date    2020-08-13 17:37:08
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
	ListNode *getIntersectionNode(ListNode *headA,
	                              ListNode *headB) {
		int x = foo(headA);
		int y = foo(headB);
		if (x > y) {
			for (int i = 0; i < x-y; ++i) {
				headA = headA->next;
			}
		} else {
			for (int i = 0; i < y-x; ++i) {
				headB = headB->next;
			}
		}
		while(headA) {
			if (headA == headB) {
				return headA;
			}
		}
		return nullptr;
	}
	int foo(ListNode *p) {
		int ans = 0;
		while (p) {
			++ans;
			p = p->next;
		}
		return ans;
	}
};