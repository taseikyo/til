/**
 * @date    2020-09-03 20:26:24
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
  public:
	vector<vector<int>> Print(TreeNode* pRoot) {
		if (!pRoot) {
			// 弱智牛客，{{}} 竟然报错
			// return {{}};
			return {};
		}
		vector<vector<int>> ans;
		queue<TreeNode*> q;
		q.push(pRoot);
		while (q.size()) {
			int n = q.size();
			vector<int> tmp;
			while (n--) {
				auto node = q.front();
				q.pop();
				tmp.push_back(node->val);
				if (node->left) {
					q.push(node->left);
				}
				if (node->right) {
					q.push(node->right);
				}
			}
			ans.push_back(tmp);
		}
		return ans;
	}
};