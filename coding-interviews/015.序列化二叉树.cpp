/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-10 15:17:50
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/cf7e25aa97c04cc1a68c8f040e71fb84?tpId=13&&tqId=11214&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
 * 请实现两个函数，分别用来序列化和反序列化二叉
 * 二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。
 *
 * 二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。
 *
 * 例如，我们可以把一个只有根节点为1的二叉树序列化为"1,"，然后通过自己的函数来解析回这个二叉树
 */


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};

// 下面是从讨论区 copy 过来的，根据跟题目要求还是有一定距离
// 题目是要求应该是全部字符串话，然后需要在两个数直接弄个特殊字符表示间隔
// 他这个做法直接不需要间隔啥的，不过也是个思路，毕竟通过了测试...
typedef TreeNode node;
typedef TreeNode* pnode;
typedef int* pint;
class Solution {
	vector<int> buf;
	void dfs(pnode p) {
		if (!p) buf.push_back(0x23333);
		else {
			buf.push_back(p -> val);
			dfs(p -> left);
			dfs(p -> right);
		}
	}
	pnode dfs2(pint& p) {
		if (*p == 0x23333) {
			++p;
			return NULL;
		}
		pnode res = new node(*p);
		++p;
		res -> left = dfs2(p);
		res -> right = dfs2(p);
		return res;
	}
  public:
	char* Serialize(TreeNode *p) {
		buf.clear();
		dfs(p);
		int *res = new int[buf.size()];
		for (unsigned int i = 0; i < buf.size(); ++i) res[i] = buf[i];
		return (char*)res;
	}
	TreeNode* Deserialize(char *str) {
		int *p = (int*)str;
		return dfs2(p);
	}
};