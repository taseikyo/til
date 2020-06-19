/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 11:55:22
 * @link    github.com/taseikyo
 */

#include <stdio.h>

int main(int argc, char const *argv[]) {
	int * p; // p是个变量名字, int * 表示该p变量只能存储int类型变量的地址
	int i = 10;
	int j;

	p = &i;
	j = *p; // 等价于 j = i;
	printf("i = %d, j = %d, *p = %d\n", i, j, *p);

	// p = 10;  // error

	return 0;
}