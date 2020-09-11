> @Date    : 2020-09-11 17:14:02
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# STRNCPY 与 STRNCAT 当 N 大于字符串长度时的区别

> 原文地址 [www.it610.com](https://www.it610.com/article/1678261.htm) 2015-11-07 14:38

- strncat 是将 s2 最多 n 个字符连接接到 s1，如果 n 小于或等于 s2 的长度（不包括结束符 '\0'），不管是否到了字符串末尾，都会在最后结果后面加上一个 '\0'；
	- 如果 n 大于 s2 的长度，那么只连接包括 s2 结束符在内的 strlen(s2)+1 个字符，此时 strncat 与 strcat 得到同样的结果。
- strncpy 是将最多 n 个字符复制到 s1 起始指针的位置，如果 n 小于或等于 s2 的长度，只复制这 n 个字符；
	- 如果 n 大于 s2 的长度，那么除了复制 s2 的全部字符（不包括它的结束符），还会在末尾补上 n-strlen(s2) 个 '\0'

```C++
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
	char a[11] = "123abcdefg";
	char b[] = "xyz";
	char c[] = "mn";

	strcpy(a, c);
	for (int i = 0; i < 11; ++i) {
		cout << a[i];
	}
	cout << endl;

	strncat(a, b, 6);
	for (int i = 0; i < 11; ++i) {
		cout << a[i];
	}
	cout << endl;

	strncpy(a, b, 6);
	for (int i = 0; i < 11; ++i) {
		cout << a[i];
	}
	cout << endl;

	return 0;
}
```

```bash
λ a.exe
mn abcdefg
mnxyz defg
xyz   defg
```
