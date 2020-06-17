/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 18:29:41
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/529d3ae5a407492994ad2a246518148a?tpId=13&&tqId=11167&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入一个链表，输出该链表中倒数第k个结点。
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
	ListNode* FindKthToTail(ListNode* head, unsigned int k) {
		ListNode* p = head;
		int n = 0;
		while (p) {
			n++;
			p = p->next;
		}
		if (k > n) {
			return NULL;
		} else if (k == n) {
			return head;
		}
		n -= k;
		while (n--) {
			head = head->next;
		}
		return head;
	}
};