> @Date    : 2020-07-29 15:48:17
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 引用折叠和完美转发

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/50816420)

阅读本文需要具有的预备知识：

*   左值和右值的基本概念
*   模板推导的基本规则
*   若无特殊说明，本文中的大写字母`T`泛指任意的数据类型

**引用折叠**
--------

我们把 **引用折叠** 拆解为 **引用**和 **折叠** 两个短语来解释。

首先，**引用**的意思众所周知，当我们使用某个对象的别名的时候就好像直接使用了该对象，这也就是引用的含义。在 C++11 中，新加入了右值的概念。所以引用的类型就有两种形式：左值引用`T&`和右值引用`T&&`。

其次，解释一下折叠的含义。所谓的折叠，就是多个的意思。上面介绍引用分为左值引用和右值引用两种，那么将这两种类型进行排列组合，就有四种情况：

```
- 左值-左值 T& &
- 左值-右值 T& &&
- 右值-左值 T&& &
- 右值-右值 T&& &&
```

**这就是所谓的引用折叠！引用折叠的含义到这里就结束了。**

**但是**，当我们在 IDE 中敲下类似这样的代码：

```
// ...
int a = 0;
int &ra = a;
int & &rra = ra;  // 编译器报错：不允许使用引用的引用！
// ...
```

**WTF ! 既然不允许使用，为啥还要有引用折叠这样的概念存在 ？!**

**原因就是：引用折叠的应用场景不在这里！！**

下面我们介绍引用折叠在模板中的应用：_完美转发_。在介绍完美转发之前，我们先介绍一下_万能引用_。

**万能引用**
--------

所谓的**万能引用**并不是 C++ 的语法特性，而是我们利用现有的 C++ 语法，自己实现的一个功能。因为这个功能既能接受左值类型的参数，也能接受右值类型的参数。所以叫做万能引用。

万能引用的形式如下：

```
template<typename T>
ReturnType Function(T&& parem)
{
    // 函数功能实现
}
```

接下来，我们看一下为什么上面这个函数能**万能引用**不同类型的参数。

为了更加直观的看到效果，我们借助`Boost`库的部分功能，重写我们的万能引用函数：

_如果不了解 Boost 库也没关系，Boost 库主要是为了帮助大家看到模板里参数类型）_

```
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;  

template<typename T>
void PrintType(T&& param)
{
    // 利用Boost库打印模板推导出来的 T 类型
	cout << "T type：" << type_id_with_cvr<T>().pretty_name() << endl; 
    
    // 利用Boost库打印形参的类型
	cout << "param type:" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

int main(int argc, char *argv[])
{
	int a = 0;                              // 左值
	PrintType(a);                           // 传入左值

	int &lvalue_refence_a = a;              // 左值引用
	PrintType(lvalue_refence_a);            // 传入左值引用

	PrintType(int(2));                      // 传入右值
}
```

通过上面的代码可以清楚的看到，`void PrintType(T&& param)`可以接受任何类型的参数。嗯，真的是万能引用！**到这里的话，万能引用的介绍也就结束了。**但是我们只看到了这个东西可以接受任何的参数，却不知道为什么它能这么做。

下面，我们来仔细观察并分析一下`main`函数中对`PrintType()`的各个调用结果。

1.  传入左值

```
int a = 0;                              // 左值
PrintType(a);                           // 传入左值
/***************************************************/
输出：T type      : int &
      param type  : int &
```

我们将 T 的推导类型`int&`带入模板，得到实例化的类型：

```
void PrintType(int& && param)
{
   // ...
}
```

**重点来了！编译器将 T 推导为 int& 类型。当我们用 int& 替换掉 T 后，得到 int & &&。**

**MD，编译器不允许我们自己把代码写成 int& &&，它自己却这么干了 =。=**

**那么 int & && 到底是个什么东西呢？！（它是引用折叠，刚开始就说了啊 =。=）**

下面，就是**引用折叠的精髓了**。

```
所有的引用折叠最终都代表一个引用，要么是左值引用，要么是右值引用。

规则就是：

如果任一引用为左值引用，则结果为左值引用。否则（即两个都是右值引用），结果为右值引用。

                                                                         《Effective Modern C++》
```

也就是说，`int& &&`等价于`int &`。`void PrintType(int& && param)` == `void PrintType(int& param)`

所以传入右值之后，函数模板推导的最终版本就是：

```
void PrintType(int& param)
{
   // ...
}
```

所以，它能接受一个左值`a`。

**现在我们重新整理一下思路：**编译器不允许我们写下类似`int & &&`这样的代码，但是它自己却可以推导出`int & &&`代码出来。它的理由就是：我 (编译器) 虽然推导出`T`为`int&`，但是我在最终生成的代码中，**利用引用折叠规则**，将`int & &&`等价生成了`int &`。推导出来的`int & &&`只是过渡阶段，最终版本并不存在。所以也不算破坏规定咯。

```
关于有的人会问，我传入的是一个左值a,并不是一个左值引用，为什么编译器会推导出T 为int &呢。

首先，模板函数参数为 T&& param,也就是说，不管T是什么类型，T&&的最终结果必然是一个引用类型。如果T是int, 那么T&& 就是 int &&；如果T为 int &，那么 T &&(int& &&) 就是&，如果T为&&,那么T &&(&& &&) 就是&&。很明显，接受左值的话，T只能推导为int &。
```

2. 明白传入左值的推导结果，剩下的几个调用结果就很明显了：

```
int &lvalue_refence_a = a;              //左值引用
PrintType(lvalue_refence_a);            // 传入左值引用
/*
 * T type      : int &
 * T &&        : int & &&
 * param type  : int &
*/

PrintType(int(2));                      // 传入右值
/*
 * T type      : int
 * T &&        : int &&
 * param type  : int &&
*/
```

1.  **以上就是万能引用的全部了。总结一下，万能引用就是利用模板推导和引用折叠的相关规则，生成不同的实例化模板来接收传进来的参数。**

**完美转发**
--------

好了，有了万能引用。当我们既需要接收左值类型，又需要接收右值类型的时候，再也不用分开写两个重载函数了。那么，什么情况下，我们需要一个函数，既能接收左值，又能接收右值呢？

答案就是：转发的时候。

于是，我们马上想到了万能引用。又于是兴冲冲的改写了以上的代码如下：

```
/*
 *  Boost库在这里已经不需要了，我们将其拿掉，可以更简洁的看清楚转发的代码实现
 */

#include <iostream>
using namespace std;

// 万能引用，转发接收到的参数 param
template<typename T>
void PrintType(T&& param)
{
	f(param);  // 将参数param转发给函数 void f()
}

// 接收左值的函数 f()
template<typename T>
void f(T &)
{
	cout << "f(T &)" << endl;
}

// 接收右值的函数f()
template<typename T>
void f(T &&)
{
	cout << "f(T &&)" << endl;
}

int main(int argc, char *argv[])
{
	int a = 0;
	PrintType(a);//传入左值
	PrintType(int(0));//传入右值
}
```

我们执行上面的代码，按照预想，在 main 中我们给 PrintType 分别传入一个左值和一个右值。PrintType 将参数转发给 f() 函数。f() 有两个重载，分别接收左值和右值。

正常的情况下,`PrintType(a);`应该打印`f(T&)`,`PrintType(int());`应该打印`f(T&&)`。

**但是**，真实的输出结果是

```
f(T &);
f(T &);
```

为什么明明传入了不同类型的值，但是`void f()`函数只调用了`void f(int &)`的版本。这说明，不管我们传入的参数类型是什么，在`void PrintType(T&& param)`函数的内部，`param`都是一个左值引用！

**没错，事实就是这样。当外部传入参数给 PrintType 函数时，param 既可以被初始化为左值引用，也可以被初始化为右值引用，取决于我们传递给 PrintType 函数的实参类型。但是，当我们在函数 PrintType 内部，将 param 传递给另一个函数的时候，此时，param 是被当作左值进行传递的。** _应为这里的 param 是个具名的对象。我们不进行详细的探讨了。大家只需要己住，任何的函数内部，对形参的直接使用，都是按照左值进行的。_

**WTF，万能引用内部形参都变成了左值！那我还要什么万能引用啊！直接改为左值引用不就好了！！**

**别急，我们可以通过一些其它的手段改变这个情况，比如使用 std::forward 。**

在万能引用的一节，我们应该有所感觉了。使用万能引用的时候，如果传入的实参是个右值 (包括右值引用)，那么，模板类型 T 被推导为 实参的类型（没有引用属性），如果传入实参是个左值，T 被推导为左值引用。**也就是说，模板中的 T 保存着传递进来的实参的信息，我们可以利用 T 的信息来强制类型转换我们的 param 使它和实参的类型一致。**

具体的做法就是，将模板函数`void PrintType(T&& param)`中对`f(param)`的调用，改为`f(std::forward<T>(param));`然后重新运行一下程序。输出如下：

```
f(T &);
f(T &&);
```

**嗯，完美的转发！**

那么，`std::forward`是怎么利用到 T 的信息的呢。

`std::forward`的源码形式大致是这样：

```
/*
 *  精简了标准库的代码，在细节上可能不完全正确，但是足以让我们了解转发函数 forward 的了
 */ 

template<typename T>
T&& forward(T ¶m)
{
	return static_cast<T&&>(param);
}
```

我们来仔细分析一下这段代码：

**我们可以看到，不管 T 是值类型，还是左值引用，还是右值引用，T & 经过引用折叠，都将是左值引用类型。也就是 forward 以左值引用的形式接收参数 param, 然后 通过将 param 进行强制类型转换 static_cast<T&&> （），最终再以一个 T&& 返回**

所以，我们分析一下传递给 PrintType 的实参类型，并将推导的 T 类型代入 forward 就可以知道转发的结果了。

1. 传入 PrintType 实参是右值类型：  
根据以上的分析，可以知道 T 将被推导为值类型，也就是不带有引用属性，假设为 int 。那么，将 T = int 带入 forward。

```
int&& forward(int ¶m)
{
	return static_cast<int&&>(param);
}
```

`param`在 forward 内被强制类型转换为 int &&_(static_cast<int&&>(param))_, 然后按照 int && 返回，两个右值引用最终还是右值引用。最终保持了实参的右值属性，转发正确。

2. 传入 PrintType 实参是左值类型：

根据以上的分析，可以知道 T 将被推导为左值引用类型，假设为 int&。那么，将 T = int& 带入 forward。

```
int& && forward(int& &param)
{
	return static_cast<int& &&>(param);
}
```

引用折叠一下就是：

```
int& forward(int& param)
{
	return static_cast<int&>(param);
}
```

看到这里，我想就不用再多说什么了。传递给 PrintType 左值，forward 返回一个左值引用，保留了实参的左值属性，转发正确。

**到这里，完美转发也就介绍完毕了。**

**总结一下就是，通过引用折叠，我们实现了万能模板。在万能模板内部，利用 forward 函数，本质上是又利用了一遍引用折叠，实现了完美转发。其中，模板推导扮演了至关重要的角色。**