/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 14:54:04
 * @link    github.com/taseikyo
 */


/**
 * https://www.nowcoder.com/practice/435fb86331474282a3499955f0a41e8b?tpId=13&&tqId=11191&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
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
	int TreeDepth(TreeNode* pRoot) {
		if (not pRoot) {
			return 0;
		}
		return max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
	}

	// 使用类似层次遍历（004）的方式获取深度
	int TreeDepth(TreeNode* pRoot) {
		if (not pRoot) {
			return 0;
		}
		vector<TreeNode*> v;
		int ans;
		v.push_back(pRoot);
		while (v.size()) {
			int len = v.size();
			while (len--) {
				pRoot = v.front();
				v.erase(v.begin());
				if (pRoot->left) {
					v.push_back(pRoot->left);
				}
				if (pRoot->right) {
					v.push_back(pRoot->right);
				}
			}
			ans++;
		}
		return ans;
	}
};