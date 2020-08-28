/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-15 22:05:48
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
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
    	node->next = node->next->next;
    }
};