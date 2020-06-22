/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 15:09:48
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 直接使用分治，中间元素作为根节点，左半部分为左子树，右半部分为右子树，正好递归
class Solution {
  public:
	TreeNode* sortedListToBST(ListNode* head) {
		if (!head) {
			return nullptr;
		}
		if (!head->next) {
			return new TreeNode(head->val);
		}
		ListNode *pre, *slow, *fast;
		pre = nullptr;
		slow = fast = head;
		while (fast && fast->next) {
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		TreeNode* root = new TreeNode(slow->val);
		root->left = sortedListToBST(head);
		root->right = sortedListToBST(slow->next);
		return root;
	}
};

// 从 discussion 收的，思路类似，不过是把所有值放到 vector
// 不需要每次遍历来获取中点
class Solution {
  public:
	void Help(vector<int>& nums, TreeNode* &curr, int begin, int end) {
		if (begin < 0 or end < 0 or begin > end) {
			return;
		}

		int mid = (begin + end) / 2;
		curr = new TreeNode(nums[mid]);
		Help(nums, curr->left, begin, mid - 1);
		Help(nums, curr->right, mid + 1, end);
	}

	TreeNode* sortedListToBST(ListNode* head) {
		ListNode* curr = head;
		vector<int> nums;
		while (curr) {
			nums.push_back(curr->val);
			curr = curr->next;
		}

		TreeNode* root;
		if (nums.size() == 0) {
			return NULL;
		}
		if (nums.size() == 1) {
			return new TreeNode(nums[0]);
		}
		Help(nums, root, 0, nums.size() - 1);
		return root;
	}
};