/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-05 16:15:37
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/b736e784e3e34731af99065031301bca?tpId=13&&tqId=11177&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
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
	vector<vector<int>> all;
	vector<int> list;
	vector<vector<int>> FindPath(TreeNode* root, int num) {
		if (! root) {
			return all;
		}
		list.push_back(root->val);
		num -= root->val;
		if (num == 0 && !root->left && !root->right) {
			all.push_back(list);
		}
		FindPath(root->left, num);
		FindPath(root->right, num);
        list.pop_back();
		return all;
	}
};