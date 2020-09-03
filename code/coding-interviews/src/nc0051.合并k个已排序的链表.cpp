/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 21:26:55
 * @link    github.com/taseikyo
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if (lists.empty()) {
			return nullptr;
		}
		return mergeKLists(lists, 0, lists.size() - 1);
	}
	ListNode *mergeKLists(vector<ListNode *> &lists, int st, int ed) {
		if (st > ed) {
			return nullptr;
		}
		if (st == ed) {
			return lists[st];
		}
		int mid = st + (ed - st) / 2;
		auto p1 = mergeKLists(lists, st, mid);
		auto p2 = mergeKLists(lists, mid + 1, ed);
		return merge(p1, p2);
	}
	ListNode *merge(ListNode *p1, ListNode *p2) {
		if (!p1) {
			return p2;
		}
		if (!p2) {
			return p1;
		}
		if (p1->val < p2->val) {
			p1->next = merge(p1->next, p2);
			return p1;
		} else {
			p2->next = merge(p1, p2->next);
			return p2;
		}
	}
};