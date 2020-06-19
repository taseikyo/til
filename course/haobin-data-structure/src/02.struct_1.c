/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-19 12:59:34
 * @link    github.com/taseikyo
 */

#include <stdio.h>
#include <string.h>

struct Student {
	int sid;
	char name[200];
	int age;
}; //分号不能省

int main(int argc, char const *argv[]) {

	struct Student st = {1000, "zhangsan", 20};
	printf("%d  %s  %d\n", st.sid, st.name, st.age);

	st.sid = 99;
	//st.name = "lisi";  //error
	strcpy(st.name, "lisi");
	st.age = 22;
	printf("%d  %s  %d\n", st.sid, st.name, st.age);

	//printf("%d %s %d\n", st);  //error
	return 0;
}