/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-20 14:43:12
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
	vector<int> nextLargerNodes(ListNode* head) {
		if (!head) {
			return {};
		}
		int n = length(head);
		vector<int> ans(n, 0);
		// index, val
		vector<pair<int, int>> stack;
		int index = 0;
		while (head) {
			if (stack.empty() || head->val <= stack.back().second) {
				stack.push_back({index, head->val});
				head = head->next;
				index++;
			} else {
				while (stack.size() && head->val > stack.back().second) {
					auto tmp = stack.back();
					ans[tmp.first] = head->val;
					stack.pop_back();
				}
			}
		}
		return ans;

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