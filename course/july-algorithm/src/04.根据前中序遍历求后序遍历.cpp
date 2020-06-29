/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 13:43:18
 * @link    github.com/taseikyo
 */

void InPre2Post(char* inorder, char* preorder, int length) {
	TreeNode* node = new TreeNode;
	node->elem = *preorder;
	int nRoot = 0;
	for (; nRoot < length; nRoot++){
		if (inorder[nRoot] == *preorder)
			break;
	}
	InPre2Post(inorder, preorder + 1, nRoot);
	InPre2Post(inordertnRoot + 1, preorder + nRoot + 1,
	           length - (nRoot + 1));
	cout << node->elem << endl;
	return;
}