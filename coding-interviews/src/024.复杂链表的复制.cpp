/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-17 21:15:16
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/f836b2c43afc4b35ad6adc41ec941dba?tpId=13&&tqId=11178&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针random指向一个随机节点），请对此链表进行深拷贝，并返回拷贝后的头结点。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
 */
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
// 这题有点东西，过程可以看 images/024.复杂链表的复制.jpg
/*
    1、复制每个节点，如：复制节点A得到A1，将A1插入节点A后面
    2、遍历链表，A1->random = A->random->next;
    3、将链表拆分成原链表和复制后的链表
*/
class Solution {
  public:
	RandomListNode* Clone(RandomListNode* head) {
		if (!head) {
			return NULL;
		}
		// 1. 复制 节点
		RandomListNode* cur = head;
		while (cur) {
			RandomListNode* node = new RandomListNode(cur->label);
			node->next = cur->next;
			cur->next = node;
			cur = node->next;
		}
		// 2. 复制 random
		cur = head;
		while (cur) {
			if (cur->random) {
				cur->next->random = cur->random->next;
			}
			cur = cur->next->next;
		}
		// 3. 拆分
		cur = head;
		RandomListNode* ret = head->next;
		RandomListNode* tail;
		while (cur->next) {
			tail = cur->next;
			cur->next = tail->next;
			cur = tail;
		}
		return ret;
	}
};