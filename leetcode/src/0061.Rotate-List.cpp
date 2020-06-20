/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 12:09:18
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
	ListNode* rotateRight(ListNode* head, int k) {
		// 相当于把最后 k 个放到开头
		if (!head) {
			return head;
		}
		int n = length(head);
		if (k % n == 0) {
			return head;
		} else if (k > n) {
			k %= n;
		}
		// 0-n-k, n-k-最后
		k = n - k;
		ListNode* pre, *p = head;
		while (k--) {
			pre = p;
			p = p->next;
		}
		pre->next = nullptr;
		pre = head;
		head = p;
		while (p->next) {
			p = p->next;
		}
		p->next = pre;
		return head;
	}
	int length(ListNode* head) {
		int ans = 0;
		while (head) {
			ans++;
			head = head->next;
		}
		return ans;
	}
};

class Solution {
  public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head) {
			return head;
		}

		int n = 1;
		auto tail = head;
		while (tail->next) {
			++n;
			tail = tail->next;
		}
		k %= n;

		if (k != 0) {
			tail->next = head;

			auto newTail = head;
			k = n - 1 - k;
			while (k-- != 0) {
				newTail = newTail->next;
			}

			head = newTail->next;
			newTail->next = nullptr;
		}

		return head;
	}
};