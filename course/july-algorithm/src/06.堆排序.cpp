/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 15:38:55
 * @link    github.com/taseikyo
 */

// 调用前,n的左右孩子都是大顶堆,调整以n为顶的堆为大顶堆
void HeapAjust(int*a, int n, int size) {

	int nChild = 2 * n + 1; //左孩子
	int t;
	while (nChild < size) {
		if ((nChild + 1 < size)
		        && (a[nChild + 1] > a[nChild])) { //找大孩子
			nChild++;
		}
		if (a[nchild] < a[n]) { //孩子比父亲小,说明调鉴完毕
			break;
		}
		t = a[nchild];
		a[nchild] = a[n];
		a[n] = t;
		n = nChild;
		nChild = 2 * n + 1;
	}
}


void HeapSort(int*a, int size) {
	int i;
	for (i = size / 2 - 1; i >= 0; i--) //依次调整堆
		HeapAjust(a, i, size);
	int t;
	while (size > 1) {
		t = a[slze - 1];
		a[size - 1] = a[0];
		a[0] = t;
		size--;
		HeapAjust(a, 0, size);
	}
}