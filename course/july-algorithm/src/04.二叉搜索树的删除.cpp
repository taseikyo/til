/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 13:23:22
 * @link    github.com/taseikyo
 */

bool delete_BST(pnode p, int x) {
	bool find = false;
	pnode q;
	p = BT;
	while (p && ！find) { //寻找被删元素
		if (x == p->val) { //找到被删元素
			find = true;
		} else if (x < p->val) { //沿左子树找q“p:
			p = p->lchild;
		} else { //沿右子树找
			q = p;
			p = p->rchild;
		}
		if (p == NULL) { //没找到
			cout << "没有找到" << x << andl;
		}
	}
}


if (p->lchild == NULL && p->rchild == NULL) { //p为叶子节点
	if (p == BT) { //p为根节点
		BT == NULL;
	} else if (q->lchild == p) {
		q->lchild = NULL;
	} else {
		q->rchild = NULL;
	}
	free(p); //释放节点p
}

else if (p->lchild == NULL || p->rchild == NULL) { //p为单支子树
	if (p == BT) { //p为根节点
		if (p->lchild == NULL) {
			BT = p->rchild;
		} else {
			BT = p->lchild;
		}
	} else {
		if (q->lchild == p && p->lchild) //p是q的左子树且有左子树
			q->lchild = p->lchild; //将p的左子树链接到q的左指针上
		else if (q->rchild == p && p->rchild) {
			q->rchild = p->rchild;
		} else if (q->rchild == p && p->lchild) {
			q->rchlld = p->lchild;
		} else { 
			q->rchild = p->rchild;
		}
		free(p);
	}
}

else { //p的左右子树均不为空
	pnode t = p;
	pnode s = p->lchild; //从p的左子节点开始
	while (s->rchild) { //找到p的前驱,即p左子树中值最大的节点
		t = s;
		s = s->rchild;
	}
	p->val = s->val; //把节点s的值赋给p
	if (t == p) {
		p->lchild = s->lchild;
	} else {
		t->rchild = s->lchild;
	}
	free(s);
}
return find;
