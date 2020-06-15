/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 22:12:34
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
// 有个坑是 0+0 和 溢出
class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int sum = foo(l1) + foo(l2);
		ListNode* dummy = new ListNode(0);
		while (sum) {
			ListNode* p = new ListNode(sum % 10);
			ListNode* tmp = dummy->next;
			dummy->next = p;
			p->next = tmp;
			sum /= 10;
		}
		return dummy->next ? dummy->next : dummy;
	}
	int foo(ListNode*l) {
		int sum = 0;
		while (l) {
			sum = sum * 10 + l->val;
			l = l->next;
		}
		return sum;
	}
};

class Solution {
  public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		stack<int> stackL1, stackL2;
		while (l1) {
			stackL1.push(l1->val);
			l1 = l1->next;
		}
		while (l2) {
			stackL2.push(l2->val);
			l2 = l2->next;
		}

		ListNode *dummy = new ListNode(0);
		int carry = 0, num1, num2;

		while (!stackL1.empty() || !stackL2.empty() || carry) {
			if (!stackL1.empty()) {
				num1 = stackL1.top();
				stackL1.pop();
			} else num1 = 0;

			if (!stackL2.empty()) {
				num2 = stackL2.top();
				stackL2.pop();
			} else num2 = 0;

			int sum = num1 + num2 + carry;
			int value = sum % 10;
			carry = sum / 10;

			ListNode *newNode = new ListNode(value);
			newNode->next = dummy->next;
			dummy->next = newNode;
		}

		return dummy->next;
	}
};