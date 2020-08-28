/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 18:32:17
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&&tqId=11156&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
 */

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
// 这是个挺赖皮的方法，直接反转 vector 就完事了
class Solution {
  public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> v;
		while (head) {
			v.push_back(head->val);
			head = head->next;
		}
		reverse(v.begin(), v.end());
		return v;
	}
};