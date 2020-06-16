/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-16 23:06:23
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
    bool isPalindrome(ListNode* head) {
        ListNode* p = head;
        int len = 0;
        while (p) {
        	len++;
        	p = p->next;
        }
        p = head;
        while(len--) {
        	p = p->next;
        }
        p = reverse(p);
        while (p) {
        	if (p->val != head->val) {
        		return false;
        	}
        	p = p->next;
        }
        return true;
    }
    ListNode* reverse(ListNode* p) {
    	ListNode* dummy = new ListNode(-1);
    	ListNode* tail = dummy;
    	while (p) {
			ListNode* tmp = p->next;
    		p->next = tail->next;
    		tail->next = p;
    		p = tmp;
    	}
    	return dummy->next;
    }
};