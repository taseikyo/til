/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 22:18:26
 * @link    github.com/taseikyo
 */

class Solution {
	public：ListNode*addTwoNumbers(ListNode * l1, ListNode * l2) {
		ListNode dummy( -1); //头节点
		int carry = 0;
		ListNode*prev = &dummy;
		for (ListNode*pa = l1, *pb = l2;
		        pa || pb ;
		        pa = pa  ? pa->next : nullptr,
		        pb = pb  ? pb->next : nullptr,
		        prev = prev->next) {
			const int ai = pa == nullptr ? 0：pa->val;
			const int bi = pb == nullptr ? 0：pb->val;
			const int value = (ai + bi + carry) % 10;
			carry = (ai + bi + carry) / 10;
			prev->next = new Listlode(value); //尾插法
		}
		if (carry > 0)
			prev->next = new ListNode(carry);
		return dummy.next;
	}
};