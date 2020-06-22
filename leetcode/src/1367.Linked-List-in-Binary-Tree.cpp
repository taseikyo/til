/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 15:22:46
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
class Solution {
  public:
	bool isSubPath(ListNode* head, TreeNode* root) {
		if (!root) {
			return false;
		}
		bool ans = false;
		if (head->val == root->val) {
			ans = match(head, root);
		}
		if (ans) {
			return true;
		}
		return isSubPath(head, root->left) || isSubPath(head, root->right);
	}

	bool match(ListNode* head, TreeNode* root) {
		if (!head) {
			return true;
		}
		if (!root) {
			return false;
		}
		if (head->val != root->val) {
			return false;
		}
		if (!root->left) {
			return match(head->next, root->right);
		} else if (!root->right) {
			return match(head->next, root->left);
		}
		return match(head->next, root->right)
		       || match(head->next, root->left);
	}
};

class Solution {
  public:
	bool isSubPath(ListNode* head, TreeNode* root) {
		if ( head == nullptr ) return true;

		if ( root == nullptr ) {
			return false;
		}

		return dfs(head, root) || isSubPath(head, root->left)
		       || isSubPath(head, root->right);
	}

  private:
	bool dfs(ListNode* listNode, TreeNode* treeNode) const {
		if ( listNode == nullptr ) return true;

		if ( treeNode == nullptr ) {
			return false;
		}

		if ( treeNode->val == listNode->val ) {
			if ( dfs(listNode->next, treeNode->left) ) {
				return true;
			}
			if ( dfs(listNode->next, treeNode->right) ) {
				return true;
			}
		}

		return false;
	}
};