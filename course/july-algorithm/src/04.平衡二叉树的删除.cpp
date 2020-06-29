/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 14:27:14
 * @link    github.com/taseikyo
 */

template<class T>
void AVLTree<T>::Deletepri(TreeNode<T>*&node, T x) {
	if (node == NULL) return; // 没有找到值是x的节点
	if (x < node->data) {
		// 如果×小于节点的值, 就继续在节点的左子树中删除x
		Deletepri(node->lson, x)
		if (2 == height(node->rson) - height(node->lson))
			if (node->rson->lsonl != NULL
			        && (height(node->rson->lson) > height(node->rson->rson)))
				DoubleRotateRL(node);
			else
				SingRotateRight(node);
	} else if (x > node->data) {
		// 如果x大于节点的值,就继续在节点的右子树中删除x
		Deletepri(node->rson, x);
		if (2 == height(node->lson) - height(node->rson))
			if (node->lson->rson != NULL
			        && (height(node->lson->rson) > height(node->lson->lson)))
				DoubleRotateLR(node);
			else
				SingRotateleft(node);
	} else {// 此节点就是要删除的点
		if (node->lson && node->rson) { // 节点右两个孩子
			TreeNode<T>* temp = node->rson;
			while (temp->lson) {
				// 找到右子树中值最小的节点
				temp = temp->lson;
			}
			node->data = temp->data;
			node->freq = temp->freq;
			Deletepri(node->rson, temp->data);
			if (2 == height(node->lson) - height(node->rson)) {
				if (node->lson->rson
				        && (height(node->lson->rson) > height(node->lson->lson)))
					DoubleRotateLR(node);
				else
					SingRotateleft(node);
			}
		} else { // 有 0、1 个孩子
			TreeNode<T>* temp = node->rson;
			if (temp->lson == NULL) { // 有右孩子或者没有孩子
				node = node->rson;
			} else if (temp->rson == NULL) { // 有左孩子
				node = node->lson;
			}
			delete(temp);
			temp = NULL;
		}
	}
	if (node == NULL) {
		return;
	}
	node->hgt = Max(height(node->lson), height(node->rson));
	return;
}

// 删除接口
template<class T>
void AVLTree<T>::Delete(T x) {
	Deletepri(root, x);
}