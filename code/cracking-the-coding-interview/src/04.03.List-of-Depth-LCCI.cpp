/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 21:33:19
 * @link    github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
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
	vector<ListNode*> listOfDepth(TreeNode* tree) {
		if (!tree) {
			return {};
		}
		queue<TreeNode*> q;
		vector<ListNode*> ans;
		q.push(tree);
		while (q.size()) {
			int size = q.size();
			ListNode head(-1);
			ListNode *tail = head->next;
			for (int i = 0; i < size; ++i) {
				auto it = q.front();
				if (it->left) {
					q.push(it->left);
				}
				if (it->right) {
					q.push(it->right);
				}
				tail->next = new ListNode(it->val);
				tail = tail->next;
				q.pop();
			}
			ans.push_back(head.next);
		}
		return ans;
	}
};