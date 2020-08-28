/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 18:24:06
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=13&&tqId=11168&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入一个链表，反转链表后，输出新链表的表头。
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
	ListNode* ReverseList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* pre, * cur, *next;
		pre = NULL;
		cur = head;
		while (cur) {
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};