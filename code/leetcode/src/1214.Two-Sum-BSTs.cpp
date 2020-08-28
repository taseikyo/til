/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 21:59:32
 * @link    github.com/taseikyo
 */

// 这题是锁住的，题目如下
// Given two binary search trees, return True if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer target.
// 简单来说就是两个 bst 中是否存在两个点，其和为 target
class Solution {
  public:
	bool twoSumBSTs(ListNode* p1, ListNode* p2, int target) {
		if (!p1 || !p2) {
			return false;
		}
		if (p1->val + p2->val == target) {
			return true;
		} else if (p1->val + p2->val > target) {
			return twoSumBSTs(p1->left, p2, target)
			       || twoSumBSTs(p1, p2->left, target);
		} else {
			return twoSumBSTs(p1->right, p2, target)
			       || twoSumBSTs(p1, p2->right, target);
		}

	}
};
// 另一个方法，固定一个树，查找 target-p1->val 是否在 p2 中
class Solution {
  public:
	bool twoSumBSTs(ListNode* p1, ListNode* p2, int target) {
		if (!p1 || !p2) {
			return false;
		}
		if (foo(p1, target - p1->val)) {
			return true;
		}
		return twoSumBSTs(p1->left, p2, target)
		       || twoSumBSTs(p1->right, p2, target);
	}

	bool foo(ListNode* p, int target) {
		if (!p) {
			return false;
		}
		if (p->val == target) {
			return true;
		} else if (p->val > target) {
			return foo(p->left, target);
		} else {
			return foo(p->right, target);
		}
	}
};