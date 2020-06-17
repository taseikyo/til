/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 21:10:14
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&&tqId=11189&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入两个链表，找出它们的第一个公共结点。（注意因为传入数据是链表，所以错误测试数据的提示是用其他方式显示的，保证传入数据是正确的）
 */
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/

// 找出2个链表的长度，然后让长的先走两个链表的长度差，然后再一起走
// 很巧妙的方法
class Solution {
  public:
	ListNode* FindFirstCommonNode( ListNode* h1, ListNode* h2) {
		int l1 = len(h1);
		int l2 = len(h2);
		if (l1>l2) {
			h1 = walk(h1, l1-l2);
		} else {
			h2 = walk(h2, l2-l1);
		}
		while (h1) {
			if (h1==h2) {
				return h1;
			}
			h1 = h1->next;
			h2 = h2->next;
		}
		return NULL;
	}
	int len(ListNode* h) {
		int ans = 0;
		while (h) {
			ans++;
			h = h->next;
		}
		return ans;
	}
	ListNode* walk(ListNode* h, int x) {
		while (x--) {
			h = h->next;
		}
		return h;
	}
};