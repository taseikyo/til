/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 12:16:59
 * @link    github.com/taseikyo
 */

#include <stdio.h>

// 不是定义了一个名字叫做*p的形参, 而是定义了一个形参，该形参名字叫做p,它的类型是int *
void f(int * p) {
	*p = 100; //
}

int main(int argc, char const *argv[]) {
	int i = 9;

	f(&i);
	printf("i = %d\n", i);

	return 0;
}
