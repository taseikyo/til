/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 12:54:51
 * @link    github.com/taseikyo
 */

#include <stdio.h>

void f(int ** q) {
	*q = (int *)0xFFFFFFFF;
}

int main(int argc, char const *argv[]) {

	int i = 9;
	int * p = &i;// int  *p;  p = &i;

	printf("%p\n", p);
	f(&p);
	printf("%p\n", p);

	return 0;
}