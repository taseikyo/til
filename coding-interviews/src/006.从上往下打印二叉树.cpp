/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-03 15:08:27
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/7fe2212963db4790b57431d9ed259701?tpId=13&&tqId=11175&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
 *
 * 感觉就是层次遍历，跟 004 一样，只不过 004 要求每一行是一个 vector
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
	vector<int> PrintFromTopToBottom(TreeNode* pRoot) {
		if (not pRoot) {
			return vector<int>();
		}
		vector<TreeNode*> v;
		vector<int> ans;
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
				ans.push_back(pRoot->val);
			}
		}
		return ans;
	}
};