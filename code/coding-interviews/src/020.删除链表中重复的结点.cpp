/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 20:17:07
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/fc533c45b73a41b0b44ccba763f866ef?tpId=13&&tqId=11209&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
 */

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
  public:
	ListNode* deleteDuplication(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* dummy = new ListNode(-1);
		dummy->next = head;
		ListNode* pre = dummy;
		ListNode* cur = dummy->next;
		while (cur) {
			if (cur->next && (cur->val == cur->next->val)) {
				while (cur->next && (cur->val == cur->next->val)) {
					cur = cur->next;
				}
				pre->next = cur->next;
				cur = cur->next;
			} else {
				pre = pre->next;
				cur = cur->next;
			}
		}
		return dummy->next;
	}
};