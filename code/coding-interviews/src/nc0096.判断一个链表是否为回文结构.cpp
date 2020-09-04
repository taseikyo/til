/**
 * @date    2020-09-04 17:31:40
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
  public:
	/**
	 *
	 * @param head ListNode类 the head
	 * @return bool布尔型
	 */
	bool isPail(ListNode* head) {
		// write code here
		if (head == NULL || head->next == NULL) {
			return true;
		}

		ListNode dummy(0);
		dummy.next = head;
		ListNode *prev = &dummy;
		ListNode *fast = head;
		ListNode *slow = head;

		while (fast != NULL && fast->next != NULL) {
			fast = fast->next->next;
			prev = slow;
			slow = slow->next;
		}

		prev->next = NULL;

		ListNode *curr = slow->next;
		slow->next = NULL;
		ListNode *next;

		while (curr != NULL) {
			next = curr->next;
			curr->next = slow;
			slow = curr;
			curr = next;
		}

		ListNode *l1 = dummy.next;

		while (l1 != NULL && slow != NULL) {
			if (l1->val != slow->val) {
				return false;
			}

			l1 = l1->next;
			slow = slow->next;
		}

		return true;
	}
};