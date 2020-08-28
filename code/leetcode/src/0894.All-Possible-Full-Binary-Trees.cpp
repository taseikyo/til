/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-30 21:05:25
 * @link    github.com/taseikyo
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// g(n) n 个 bt 个数
// f(i) i 为顶点的 bt 个数
// https://leetcode-cn.com/problems/all-possible-full-binary-trees/solution/cban-ben-fu-dai-wan-zheng-de-zhu-shi-by-fuckleetco/
class Solution {
  public:
	unordered_map<int, vector<TreeNode*>>  m;
	vector<TreeNode*> allPossibleFBT(int N) {
		vector<TreeNode*> ans;
		if (m.count(N)) return m[N];
		if (N == 1) {
			ans.push_back(new TreeNode(0));
		} else  {
			//我们知道一共有N个结点，root占了1个结点，左子树可能有1，3，5，..，N-2个结点
			//对应的，右子树可能有N-2，..，5，3，1个结点
			//那么，我们可以用一个循环，找到所有可能的左右子树的可能的数量的情况，把root放进列表里
			for (int i = 1; i < N; i += 2) {
				vector<TreeNode*> left = allPossibleFBT(i);
				vector<TreeNode*> right = allPossibleFBT(N - i - 1);
				for (auto l : left) {
					for ( auto r : right) {
						TreeNode* root = new TreeNode(0);
						root -> left = l;
						root -> right = r;
						ans.push_back(root);
					}
				}
			}
		}
		m.insert({N, ans});
		return m[N];
	}
};
