/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 20:52:45
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
// copy来的方法，首先将 vector 设为-2，然后遍历数组G，将对应 vector 中的值设为 -1
// 遍历 vector，如果连续-1，如果连续n个，则最后一个保留为-1
// 最后只需要数 vector 中 -1 的个数即可
class Solution {
  public:
	int numComponents(ListNode* head, vector<int>& G) {
		ListNode *p = head, *q;
		int c = 0;
		while (p) c++, p = p->next;
		if (c == 1 && G.size() == 1) return 1;
		if (c == 1 && G.size() == 0) return 0;

		vector<int> l(c, -2);
		for (auto g : G) l[g] = -1;
		p = head, q = head->next;

		while (q) {
			if (l[p->val] == -1 && l[q->val] == -1) l[p->val] = q->val;
			q = q->next;
			p = p->next;
		}
		int ans = 0;
		for (auto x : l) if (x == -1) ans++;
		return ans;
	}
};