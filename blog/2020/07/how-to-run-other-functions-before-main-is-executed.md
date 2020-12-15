> @Date    : 2020-07-04 17:09:23
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 如何在 main 函数之前执行其它函数

- https://www.cnblogs.com/zpcoding/p/10805639.html

## 在 C 语言中 用 __attribute__ 关键字

gcc 中使用 attribute 关键字，声明 constructor 和 destructor 函数

```c
#include <stdio.h>

void before() __attribute__((constructor));
void after() __attribute__((destructor));

void before() {
	printf("this is function %s\n", __func__);
	return;
}

void after() {
	printf("this is function %s\n", __func__);
	return;
}

int main(int argc, char const *argv[]) {
	printf("this is function %s\n", __func__);
	return 0;
}

// 输出结果
// this is function before
// this is function main
// this is function after
```

## 在 C++ 中用全局对象构造函数

全局变量构造函数在 mian 之前

```c++
#include <iostream>
#include <string>

using namespace std;

class A {
public:
    A(string s) {
        str.assign(s);
        cout << str << ":A构造" <<endl;
    }
    ~A(){
        cout << str << ":A析构" <<endl;
    }
private:
    string str;
};

A test1("Global"); // 全局对象的构造

int main() {
    A test2("main");  // 局部对象的构造
    return 0;
}

// 输出结果
// Global:A构造
// main:A构造
// main:A析构
// Global:A析构
```
