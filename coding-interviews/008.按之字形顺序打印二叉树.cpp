/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 16:05:38
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/91b69814117f4e8097390d107d2efbe0?tpId=13&&tqId=11212&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
 *
 * 这题跟 004，006 类似
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
	vector<vector<int>> Print(TreeNode* pRoot) {
		if (not pRoot) {
			return vector<vector<int>>();
		}
		vector<TreeNode*> v;
		// 0: left-right
		// 1: right-left
		int direction = 0;
		vector<vector<int>> ans;
		v.push_back(pRoot);
		while (v.size()) {
			int len = v.size();
			vector<int> tmp_ans;
			while (len--) {
				pRoot = v.front();
				v.erase(v.begin());
				if (pRoot->left) {
					v.push_back(pRoot->left);
				}
				if (pRoot->right) {
					v.push_back(pRoot->right);
				}
				tmp_ans.push_back(pRoot->val);
			}
			if (direction) {
				reverse(tmp_ans.begin(), tmp_ans.end());
			}
			ans.push_back(tmp_ans);
			direction = 1 - direction;
		}
		return ans;
	}
};