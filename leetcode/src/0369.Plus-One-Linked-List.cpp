/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 15:07:26
 * @link    github.com/taseikyo
 */


/**
 * 这题是上锁的，不过问题不难
 *
Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example :

Input: [1,2,3]
Output: [1,2,4]

简单来说就是链表表示数字，现在要做加一操作
很自然的一个想法，反转-加一-再反转
 */

class Solution {
  public:
	ListNode* plusOne(ListNode* head) {
		if (!head) return head;
		ListNode *rev_head = reverse(head), *cur = rev_head, *pre = cur;
		int carry = 1;
		while (cur) {
			pre = cur;
			int t = cur->val + carry;
			cur->val = t % 10;
			carry = t / 10;
			if (carry == 0) break;
			cur = cur->next;
		}
		if (carry) pre->next = new ListNode(1);
		return reverse(rev_head);
	}
	ListNode* reverse(ListNode *head) {
		if (!head) return head;
		ListNode *dummy = new ListNode(-1), *cur = head;
		dummy->next = head;
		while (cur->next) {
			ListNode *t = cur->next;
			cur->next = t->next;
			t->next = dummy->next;
			dummy->next = t;
		}
		return dummy->next;
	}
};

// 解法二：递归

class Solution {
  public:
	ListNode* plusOne(ListNode* head) {
		if (!head) return head;
		int carry = helper(head);
		if (carry == 1) {
			ListNode *res = new ListNode(1);
			res->next = head;
			return res;
		}
		return head;
	}
	int helper(ListNode *node) {
		if (!node) return 1;
		int carry = helper(node->next);
		int sum = node->val + carry;
		node->val = sum % 10;
		return sum / 10;
	}
};

// 解法三 找到右起第一个不为9的数字
// 如果找不到这样的数字，说明所有数字均为9，那么在表头新建一个值为0的新节点，进行加1处理
// 然后把右边所有的数字都置为0即可
// 比如1->2->3，那么第一个不为9的数字为3，对3进行加1，变成4，右边没有节点了，所以不做处理，返回1->2->4。
// 再比如说8->9->9，找第一个不为9的数字为8，进行加1处理变成了9，然后把后面的数字都置0，得到结果9->0->0。
// 再来看9->9->9的情况，找不到不为9的数字，那么再前面新建一个值为0的节点，进行加1处理变成了1，把后面的数字都置0，得到1->0->0->0。

class Solution {
  public:
	ListNode* plusOne(ListNode* head) {
		ListNode *cur = head, *right = NULL;
		while (cur) {
			if (cur->val != 9) right = cur;
			cur = cur->next;
		}
		if (!right) {
			right = new ListNode(0);
			right->next = head;
			head = right;
		}
		++right->val;
		cur = right->next;
		while (cur) {
			cur->val = 0;
			cur = cur->next;
		}
		return head;
	}
};