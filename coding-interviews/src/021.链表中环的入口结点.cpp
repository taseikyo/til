/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 20:49:26
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/253d2c59ec3e4bc68da16833f79a38e4?tpId=13&&tqId=11208&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。
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
	ListNode* EntryNodeOfLoop(ListNode* head) {
		if (!head || !head->next) {
			return NULL;
		}
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow) {
				break;
			}
		}
		if (fast == slow) {
			slow = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
		return NULL;
	}
};