/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 18:26:13
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=13&&tqId=11169&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
 */

/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
  public:
	ListNode* Merge(ListNode* p1, ListNode* p2) {
		ListNode* dummy = new ListNode(-1);
		ListNode* tail = dummy;
		while (p1 && p2) {
			if (p1->val < p2) {
				tail->next = p1;
				p1 = p1->next;
			} else {
				tail->next = p2;
				p2 = p2->next;
			}
			tail = tail->next;
		}
		if (p1) {
			tail->next = p1;
		}
		if (p2) {
			tail->next = p2;
		}
		return dummy->next;
	}
};