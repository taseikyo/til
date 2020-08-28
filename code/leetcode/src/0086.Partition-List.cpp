/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 13:24:56
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

class Solution {
  public:
	ListNode* partition(ListNode* head, int x) {
		ListNode left_dummy(-1);// 头结点
		ListNode right_dummy(-1);//头结点
		auto left_cur = &left_dummy;
		auto right_cur = &right_dummy;
		for (ListNode*cur = head; cur; cur = cur->next) {
			if (cur->val < x) {
				left_cur->next = cur;
				left_cur = cur;
			} else {
				right_cur->next = cur;
				right_cur = cur;
			}
		}
		left_cur->next = right_dummy.next;
		right_cur->next = nullptr;
		return left_dummy.next;
	}
};