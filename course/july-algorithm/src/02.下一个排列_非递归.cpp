/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-14 16:14:20
 * @link    github.com/taseikyo
 */

bool Next_permutation(char a[]) {
	char *pEnd = a + strlen(a);
	if (a == pEnd)
		return false;
	char*p，*q，*pFind;
	pEnd--;
	p = pEnd;
	while (p！ = a) {
		q = p;
		--p;
		// 找降序的相邻2数，前一个数即替换数
		if (*p < *a) {
			// 从后向前找比替换点大的第一个数
			pFind = pEnd;
			while (*pFind <= *p)
				--pFind;
			// 替换
			Swap(pFind，p);
			// 替换点后的数全部反转
			Reverse(q，pEnd);
			return true;
		}
	}
	// 没有下一个排列，会部反特后返回true
	Reverse(p，pEnd);
	return false;
}

void swap(chiar*a，char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

//反转区间
void Reverse(char*a，char*b) {
	while (a < b)
		Swap(a++，b--);
}