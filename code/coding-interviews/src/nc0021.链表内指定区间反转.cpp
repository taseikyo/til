/**
 * @date    2020-09-04 16:07:10
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
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
	 * @param head ListNode类
	 * @param m int整型
	 * @param n int整型
	 * @return ListNode类
	 */
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		// 题目限定 m n 合理，则不需要判断边界
		if (m == n) {
			return head;
		}
		ListNode *mp, *mpp;
		ListNode *np, *npp;
		ListNode dummy(-1);
		dummy.next = head;
		mp = head, mpp = &dummy;
		while (--m) {
			mp = mp->next;
			mpp = mpp->next;
		}
		np = head;
		while (--n) {
			np = np->next;
		}
		npp = np->next;
		auto ret = reverseBetween(mp, np);
		mpp->next = ret.first;
		ret.second->next = npp;
		return dummy.next;
	}
	// head, tail
	pair<ListNode*, ListNode*>reverseBetween(ListNode*p,
	        ListNode*q) {
		ListNode *pre, *cur, *next;
		pre = nullptr;
		cur = p;
		auto end = q->next;
		while (cur != end) {
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return {pre, p};
	}
};