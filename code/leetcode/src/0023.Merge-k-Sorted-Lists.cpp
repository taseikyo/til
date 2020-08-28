/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 20:41:35
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
// 直接从前往后合并，本以为会超时，结果竟然过了，不过时间挺慢就是了
class Solution {
  public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty()) {
			return nullptr;
		}

		ListNode* p = lists[0];
		for (int i = 1; i < lists.size(); ++i) {
			ListNode* dummy = new ListNode(-1);
			ListNode* tail = dummy;
			ListNode* tmp = lists[i];
			while (tmp && p) {
				if (p->val < tmp->val) {
					tail->next = p;
					p = p->next;
				} else {
					tail->next = tmp;
					tmp = tmp->next;
				}
				tail = tail->next;
			}
			if (tmp) {
				tail->next = tmp;
			}
			if (p) {
				tail->next = p;
			}
			p = dummy->next;
		}
		return p;
	}
};

class Solution {
  public:
	ListNode* merge(int st, int end, vector<ListNode*>&list) {
		if (st > end)
			return NULL;
		if (st == end) 
			return list[st]; // starting list and the ending list are equal
		int m = st + (end - st) / 2;
		ListNode* l1 = merge(st, m, list); // start and mid list
		ListNode* l2 = merge(m + 1, end, list);
		return merge(l1, l2);

	}
	ListNode* merge(ListNode* l1, ListNode* l2) {
		if (l1 == NULL)return l2;
		if (l2 == NULL)return l1;
		if ( (l1->val) < (l2->val) ) {l1->next = merge(l1->next, l2); return l1;}
		else {l2->next = merge(l1, l2->next); return l2;}
	}

	ListNode* mergeKLists(vector<ListNode*>& list) {
		return merge(0, list.size() - 1, list);
	}
};