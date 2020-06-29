/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 14:20:24
 * @link    github.com/taseikyo
 */

template<class T>
void AVLTree<T>::insertpri(TreeNode<T>*&node, T x) {
	if (node == NULL) {
		//如果节点为空,就在此节点处加入x信息
		node = new TreeNode<T>();
		node->data = x;
		return;
	}

	if (node->data > x) {
		// 如果×小于节点的值，就继续在节点的左子树中插入x
		insertpri(node->lson, x);
		if (2 == height(node->lson) - height(node->rson))
			if (x < node->lson->data)
				SingRotateLeft(node);
			else
				DoubleRotateLR(node);
	} else if (node->data < x) {
		//如果x大于节点的值,就继续在节点的右子树中插入x
		insertpri(node->rson, x);
		if (2 == height(node->rson) - height(node->lson))
			// 如果高度之差为2
			if (x > node->rson->data)
				SingRotateRight(node);
			else
				DoubleRotateRL(node);
	} else ++(node->freq); //如果相等,就把频率加1
	node->hgt = Max(height(node->lson), height(node->rson));
}


// 插入接口
template<classT>
void AVLTree<T>::insert(Tx) {
	insertpri(root, x);
}