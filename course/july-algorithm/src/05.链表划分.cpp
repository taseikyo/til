/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 22:34:30
 * @link    github.com/taseikyo
 */

class Solution {
	public：ListNode*partition(ListNode*head，int x) {
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