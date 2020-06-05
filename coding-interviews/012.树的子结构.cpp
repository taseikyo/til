/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-05 15:55:45
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&&tqId=11170&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
 */

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};

class Solution {
  public:
	bool HasSubtree(TreeNode* pa, TreeNode* pb) {
		if (!pa || !pb) {
			return false;
		}
		if (pa->val == pb->val) {
			bool ans = check(pa->left, pb->left)
			           && check(pa->right, pb->right);
			if (ans) {
				return true;
			}
		}
		return HasSubtree(pa->left, pb) || HasSubtree(pa->right, pb);
	}

	bool check(TreeNode* pa, TreeNode* pb) {
		if (!pb) {
			return true;
		}
		if (!pa) {
			return false;
		}
		if (pa->val != pb->val) {
			return false;
		}
		return check(pa->left, pb->left) && check(pa->right, pb->right);
	}

};