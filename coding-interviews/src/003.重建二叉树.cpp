/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-01 16:45:34
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=11157&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
 */

#include <stdio.h>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
  public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.size() == 0) {
			return NULL;
		}
		TreeNode* node = new TreeNode(pre[0]);
		int k = 0;
		for ( ; vin[k] != pre[0]; ++k) {}
		node->left = reConstructBinaryTree(vector<int>(pre.begin() + 1,
		                                   pre.begin() + 1 + k), vector<int>(vin.begin(), vin.begin() + k));
		node->right = reConstructBinaryTree(vector<int>(pre.begin() + 1 + k,
		                                    pre.end()), vector<int>(vin.begin() + 1 + k, vin.end()));
		return node;
	}

};