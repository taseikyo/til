> @Date    : 2020-08-31 09:24:54
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/sinat_18811413/article/details/104994106) [鸟哥01](https://me.csdn.net/sinat_18811413) 2020-03-20 17:11:14

# C++ shared_ptr 按引用传参不增加引用计数

```C++
#include <iostream>
#include <memory>

using namespace std;

void f(shared_ptr<int>& sp) {
    cout << "按引用传参不增加引用计数：" <<
         sp.use_count() << endl;
}

void f2(shared_ptr<int> sp) {
    cout << "按值传参增加引用计数：" << sp.use_count()
         << endl;
}
int main() {
    shared_ptr<int> sp = make_shared<int>(9);
    cout << "原始计数：" << sp.use_count() << endl;
    f(sp);
    f2(sp);
    cout << "原始计数：" << sp.use_count() << endl;

    shared_ptr<int> sp2 = sp;
    cout << "复制后，增加引用计数：" << sp.use_count()
         << endl;

    shared_ptr<int>& sp3 = sp2;
    cout << "赋值给引用，不增加引用计数：" <<
         sp3.use_count() << endl;

}
```

运行结果：

> 原始计数：1  
> 按引用传参不增加引用计数：1  
> 按值传参增加引用计数：2  
> 原始计数：1  
> 复制后，增加引用计数：2  
> 赋值给引用，不增加引用计数：2

【最后结果可知，对于传参，值传递会增加技术，而引用传递不会；对于复制，同样是这样的结论】