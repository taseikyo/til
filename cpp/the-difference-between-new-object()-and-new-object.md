> @Date    : 2020-09-01 ‏‎09:57:40
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/a2337116/article/details/96331409) [a2337116](https://me.csdn.net/a2337116) 2019-07-17 17:36:21

今天逛牛客看到这个面试题，想了一下确实不知道 2333

# new object() 和 new object 区别

## 1. new object()

> 如果有自定义默认构造函数则会调用；如果没有则会调用编译器合成的默认构造函数，对内存初始化

```C++
struct Student {
    int a;
    char * p;
};

void foo() {
    Student* pStu1 = new
    Student;  // a 和 p 值不会被初始化
    Student* pStu2 = new Student();// a = 0 , p = Null
}
```

## 2. new object

> 如果有自定义默认构造函数则会调用； 如果没有则不会调用；

```C++
struct Student {
    Student() {
        a = 50;
        p = "Hello World";
    }
    int a;
    const char* p;
};

void foo() {
    Student* pStu1 = new
    Student;      // a = 50 p = "Hello World";
    Student* pStu2 = new Student();
}
```