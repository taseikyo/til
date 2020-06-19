/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 12:53:41
 * @link    github.com/taseikyo
 */

#include <stdio.h>

void f(int * p) {
	*p = 99;
}

int main(int argc, char const *argv[]) {

	int i = 10;

	f(&i);
	printf("i = %d\n", i);

	return 0;
}
