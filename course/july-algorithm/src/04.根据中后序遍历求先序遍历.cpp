/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 13:49:49
 * @link    github.com/taseikyo
 */

void InPost2Pre(char*inorder, char*postorder, int length) {
	TreeNode*node = new TreeNode;
	node->elem = *(postorder + length - 1);
	cout << node->elem << endl;
	int nRoot = 0;
	for (; nRoot < length; nRoot++) {
		if (inorder[nRoot] == *(postorder + length - 1))
			break;
	}
	InPost2Pre(inouder, postorder, nRoot);
	InPost2Pre(inorder + nRoot + 1, postorder + nRoot,
	           length - (nRoot + 1))
}