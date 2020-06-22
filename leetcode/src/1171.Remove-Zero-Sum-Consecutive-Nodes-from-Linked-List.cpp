/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 16:11:41
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
// 来自讨论区，很有趣的解法，不太好想
class Solution {
  public:
	ListNode* removeZeroSumSublists(ListNode* head) {
		vector<int> vals;
		vector<int> sum = {0};
		ListNode* cur = head;
		while (cur) {
			vals.push_back(cur->val);
			cur = cur->next;
		}
		sum.push_back(vals[0]);
		for (int i = 1; i < vals.size(); i++) {
			sum.push_back(sum[i] + vals[i]);
		}
		ListNode* nhead = new ListNode(0);
		ListNode* ntail = nhead;
		int i = 0;
		while (i < vals.size()) {
			for (int j = vals.size(); j >= i; j--) {
				if (i == j) {
					ListNode* nnode = new ListNode(vals[i]);
					ntail->next = nnode;
					ntail = nnode;
					i++;
					break;
				} else if (sum[i] == sum[j]) {
					i = j;
					break;
				}
			}
		}
		return nhead->next;
	}
};

class Solution {
  public:
	ListNode* removeZeroSumSublists(ListNode* head) {
		ListNode dummy { -1, head};
		unordered_map<int, ListNode*> hash;
		hash[0] = &dummy;
		int sum = 0;
		while (head) {
			sum += head->val;
			if (hash.find(sum) != hash.end()) {
				auto prev = hash[sum];
				auto curr = prev->next;
				auto local = sum;
				while (curr != head) {
					local += curr->val;
					hash.erase(local);
					curr = curr->next;
				}
				prev->next = head->next;
			} else {
				hash[sum] = head;
			}
			head = head->next;
		}
		return dummy.next;
	}
};