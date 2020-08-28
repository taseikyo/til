/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 14:33:04
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/445c44d982d04483b04a54f298796288?tpId=13&&tqId=11213&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
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
		vector<vector<int>> ans;
		v.push_back(pRoot);
		while (v.size()) {
			vector<TreeNode*> tmp;
			vector<int> tmp_ans;
			for (auto i: v) {
				if (i->left) {
					tmp.push_back(i->left);
				}
				if (i->right) {
					tmp.push_back(i->right);
				}
				tmp_ans.push_back(i->val);
			}
			ans.push_back(tmp_ans);
			v = tmp;
		}
		return ans;
	}

	// 首先用个变量保存当前栈的深度，因而避免使用两个栈
	vector<vector<int>> Print(TreeNode* pRoot) {
		if (not pRoot) {
			return vector<vector<int>>();
		}
		vector<TreeNode*> v;
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
			ans.push_back(tmp_ans);
		}
		return ans;
	}


};