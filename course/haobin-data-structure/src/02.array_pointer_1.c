/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 12:37:29
 * @link    github.com/taseikyo
 */

#include <stdio.h>

int main(int argc, char const *argv[]) {
	int a[5] = {1, 2, 3, 4, 5};

	//a[3] == *(3+a);

	printf("%p\n", a + 1);
	printf("%p\n", a + 2);
	printf("%d\n", *a + 3); //*a+3等价于 a[0]+3
	return 0;
}
