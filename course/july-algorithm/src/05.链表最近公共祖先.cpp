/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 12:43:22
 * @link    github.com/taseikyo
 */

node* getLCA(node* root, node* node1, node* node2) {
	if (root == null)
		return null;
	if (root == node1 || root == node2)
		return root;
	node* left = getLCA(root->left, node1, node2);
	node* right = getLCA(root->right, node1, node2);
	if (left && right)
		return root;
	else if (left)
		return left;
	else if (right)
		return right;
	else
		return null;
}