/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 13:11:45
 * @link    github.com/taseikyo
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
	ListNode *getIntersectionNode(ListNode *ha, ListNode *hb) {
		int x1 = length(ha);
		int x2 = length(hb);
		if (x1 > x2) {
			ha = walk(ha, x1 - x2);
		} else {
			hb = walk(hb, x2 - x1);
		}
		while (ha) {
			if (ha == hb) {
				return ha;
			}
			ha = ha->next;
			hb = hb->next;
		}
		return NULL;
	}
	int length(ListNode *head) {
		int ans = 0;
		while (head) {
			head = head->next;
			ans++;
		}
		return ans;
	}
	ListNode * walk(ListNode *h, int step) {
		while (step--) {
			h = h->next;
		}
		return h;
	}
};

// 这个做法挺巧妙的，将 A 做成个环，然后利用之前找环入口的做法，牛逼！
class Solution {
  public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		if (headA == nullptr || headB == nullptr) return nullptr;

		ListNode *res = headA;
		while (res->next) {
			res = res->next;
		}
		res->next = headA;

		ListNode *slow = headB;
		ListNode *fast = headB->next;
		bool intersect = false;
		while (true) {
			if (slow == fast) {
				intersect = true;
				break;
			}
			if (!slow || !fast || !fast->next) {
				break;
			}
			slow = slow->next;
			fast = fast->next->next;
		}
		res->next = nullptr;
		if (!intersect) {
			return nullptr;
		}

		slow = headA;
		fast = headB;
		while (slow != fast) {
			if (!slow) slow = headB;
			else {
				slow = slow->next;
			}
			if (!fast) fast = headA;
			else {
				fast = fast->next;
			}
		}

		return slow;
	}
};