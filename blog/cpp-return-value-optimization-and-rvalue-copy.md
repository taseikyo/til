> @Date    : 2020-09-10 19:45:16
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

很有趣的一个问题，当一个函数返回一个局部变量，会发生几次拷贝呢？

@200914 补充，由于前天字节一面的时候问到，还好之前看了，所以赚了，今天翻出来又找了一篇看看，合起来。

- [C++ 的返回值优化以及右值拷贝](#c-的返回值优化以及右值拷贝)
- [C++ 编译器优化技术：RVO、NRVO 和复制省略](#c-编译器优化之-rvo-与-nrvo)


# C++ 的返回值优化以及右值拷贝

> 原文：https://sq.163yun.com/blog/article/170332301127245824 作者：[达芬奇密码](https://sq.163yun.com/user/165240397716357120) 2018-06-27 15:49

## Table of Contents

- [返回值优化](#返回值优化)
- [右值拷贝](#右值拷贝)

### 返回值优化

返回值优化是一个编译器优化行为，它可以减少函数调用返回时临时对象的产生以及拷贝行为。以下面代码为例

```C++
class BigData {
  public:
    BigData(const char* data, size_t size) {
        cout << this << " constructor" << endl;
        data_ = new char[size];
        memcpy(data_, data, size);
        size_ = size;
    }

    BigData(const BigData& data) {
        cout << this << " lvalue const copy constructor" << endl;
        data_ = new char[data.size_];
        memcpy(data_, data.data_, data.size_);
        size_ = data.size_;
    }

    ~BigData() {
        cout << this << " destructor" << endl;
        delete [] data_;
    }
  private:
    char* data_;
    size_t size_;
};

BigData createBigData2() {
    const char* bigData = "This is really Big data!";
    BigData data(bigData, strlen(bigData));
    return data;
}

int main() {
    BigData data = createBigData2();
}
```

在 gcc 或者 clang 添加 "-fno-elide-constructors" 编译选项，禁用返回值优化的运行结果如下：

```bash
0x7fff5fbff738 constructor
0x7fff5fbff780 lvalue const copy constructor
0x7fff5fbff738 destructor
0x7fff5fbff790 lvalue const copy constructor
0x7fff5fbff780 destructor
0x7fff5fbff790 destructor
```

我们可以看到一共调用了 3 次构造函数，第一次是 createBigData2 函数里局部变量 data 调用，一次是返回 data 时创建的临时变量调用，最后一次是临时对象赋值给 main 中的 data 调用。为了减少拷贝的次数，一个常规的写法如下：

```C++
const BigData& data = createBigData2();
```

通过常量引用延展临时变量的生命周期，运行结果如下：

```bash
0x7fff5fbff758 constructor
0x7fff5fbff788 lvalue const copy constructor
0x7fff5fbff758 destructor
0x7fff5fbff788 destructor
```

可以看到这减少了一次临时变量到调用者栈的一次拷贝。

现在我们去掉 "-fno-elide-constructors" 编译选项编译选项，允许编译器对返回值进行优化，不使用常量引用：

```C++
BigData data = createBigData2();
```

运行后的结果如下：

```bash
0x7fff5fbff788 constructor
0x7fff5fbff788 destructor
```

只剩下一次构造函数调用！没有拷贝！没有零时变量！可以看到返回值优化之后是对调用者栈中的变量直接进行操作。虽然编译器有返回值优化的能力，但是不是所有场景下都能够进行完美的返回值优化，我们来看下面的代码：

```C++
BigData createBigData3(bool first) {
    const char* bigData = "This is really Big data!";
    BigData data1(bigData, strlen(bigData)), data2(bigData,
            strlen(bigData));
    if (first) {
        return data1;
    } else {
        return data2;
    }
}

BigData data = createBigData3(true);
```

运行后输出:

```bash
0x7fff5fbff750 constructor
0x7fff5fbff740 constructor
0x7fff5fbff790 lvalue const copy constructor
0x7fff5fbff740 destructor
0x7fff5fbff750 destructor
0x7fff5fbff790 destructor
```

我们看到编译器优化掉了临时变量的拷贝，但是函数栈到调用者栈的拷贝还是没能优化掉。返回值优化可以理解为函数有一个隐藏的参数，传入的是调用者栈中将要被赋值的对象的地址，以 createBigData1 函数为例，最终的调用可能是：

```C++
createBigData2(&data);
```

所有的操作都直接在调用者栈中的变量上操作。我们再看 createBigData3，由于存在分支，编译期无法决定 data1 和 data2 哪个才是调用者栈中的 data，也就无法进行优化。

### 右值拷贝

返回值拷贝能够帮我们极大的优化程序性能，但是仍然存在无法优化的情况。当实在无法避免拷贝的时候，能不能减小拷贝的代价呢？

我们来回顾一下 C++ 中深拷贝和浅拷贝。上面代码中 BigData 类中的拷贝构造就是一个深拷贝：

```C++
BigData(const BigData& data) {
    cout << this << " lvalue const copy constructor" << endl;
    data_ = new char[data.size_];
    memcpy(data_, data.data_, data.size_);
    size_ = data.size_;
}
```

首先为 data _分配内存，然后将拷贝对象中的 data_ 内容拷贝过来。我们现在增加一个浅拷贝构造函数：

```C++
BigData(BigData& data) {
    cout << this << " lvalue non const copy constructor" << endl;
    data_ = data.data_;
    size_ = data.size_;
    data.data_ = nullptr;
    data.size_ = 0;
}
```

执行 (禁止返回值优化)：

```C++
BigData data = createBigData2();
```

输出：

```bash
0x7fff5fbff738 constructor
0x7fff5fbff780 lvalue non const copy constructor
0x7fff5fbff738 destructor
0x7fff5fbff790 lvalue const copy constructor
0x7fff5fbff780 destructor
0x7fff5fbff790 destructor
```

可以看到函数栈变量到临时变量调用了浅拷贝，临时变量到调用栈变量拷贝调用了深拷贝。在 createBigData2 中，被拷贝对象 data 是一个非常量值，所以拷贝到临时变量调用的是非常量版本的拷贝函数。在 C++11 之前临时变量只能赋值给常量引用，所以临时变量到调用者栈变量拷贝调用的是常量拷贝构造函数。在上面自定义的浅拷贝中将被拷贝对象的 data _变量设置成 nullptr，这阻止了被拷贝对象对 data_ 的内存释放，这很重要，否则拷贝完成后如果被拷贝对象析构掉了，那就会导致拷贝来的对象的 data_的指针是个野指针。

所以我认为非常量拷贝函数就是一个鸡肋的存在：

1. 临时对象到非临时对象的拷贝他无能为力
2. 默认的浅拷贝实现很危险
3. 让让拷贝的语义很费解，拷贝者在拷贝的时候还可能改变被拷贝者的某些属性，到底改了什么属性从语义上是没法知晓的  
    

从 C++11 开始又增加了一类新的拷贝函数，叫做右值拷贝，以 BigData 为例，他的定义是这样的  

```C++
BigData(BigData&& other)
```

这很有意思，非常量拷贝的参数是一个非常量引用，用 & 表示，右值拷贝的参数是一个右值引用，用 && 表示  

我们先来解释一下左值跟右值  

```C++
int x = 1;
```

上面等式中 x 是左值，1 是右值，难道在等号左边的就是左值，在等号右边的就是右值？不是的，应该说能够寻址的就是一个左值，不能够寻址的就是一个右值。数值常量是右值，零时变量是右值。相应的指向左值的引用就是一个左值引用，指向右值的引用就是一个右值引用。所以有下面的代码：  

```C++
int a    = 1; // 正确
int &b    = 1; // 错误，左值引用不能指向右值
int &&c = 1; // 正确
int &&d = a; // 错误，右值引用不能指向左值
const int& e = 1; // 正确，常量引用可以指向右值
```

常量引用是一个特例，它既能指向左值又能指向右值，因为在 C++11 之前常量引用就是唯一能指向临时变量的一个存在。  

有了右值拷贝后我们就可以很放心大胆的修改被拷贝对象了，因为我们知道那是一个右值，一个临时变量，是不可能（有例外，下面会说）被其他地方引用的，对被拷贝对象做的所有操作都被不会影响到其他地方。于是我们不用非常量拷贝，使用右值拷贝：  

```C++
BigData(BigData&& other) {
    cout << this << " rvalue copy constructor" << endl;
    data_ = data.data_;
    size_ = data.size_;
    data.data_ = nullptr;
    data.size_ = 0;
}
```

执行（禁止返回值优化）:  

```C++
BigData data = createBigData2();
```

得到结果：

```bash
0x7fff5fbff738 constructor
0x7fff5fbff780 rvalue copy constructor
0x7fff5fbff738 destructor
0x7fff5fbff790 rvalue copy constructor
0x7fff5fbff780 destructor
0x7fff5fbff790 destructor
```

可以看到每次拷贝都是浅拷贝，相比于深拷贝自然有不少性能提升。

新技能 get，我们分析下下面的代码：

```C++
BigData&& data = createBigData2();
BigData data1(data);
```

data 是一个右值引用，那么构造 data1 的时候调用哪个构造函数呢？难道不应该是右值拷贝构造函数吗？我们运行一下看下结果：

```bash
0x7fff5fbff728 constuctor
0x7fff5fbff788 rvalue copy constuctor
0x7fff5fbff728 destuctor
0x7fff5fbff778 lvalue non const copy constuctor
0x7fff5fbff778 destuctor
0x7fff5fbff788 destuctor
```

结果显示调用的是非常量拷贝函数…… 这是为什么？这里还是要重申一下右值是不能被寻址的，当 data 指向 createBigData2() 返回的临时变量的时候该临时变量就已经能够被寻址了，他已经不能算是右值！那要怎么才能让它调用右值拷贝构造函数？C++11 中提供了 move 函数，该函数的语义就是把一个左值转化为右值，下面代码就能正确的调用右值拷贝构造函数：

```C++
BigData&& data = createBigData2();
BigData data1(std::move(data));
```

最后作为一个以 iOS 开发为正当职业的程序员来说怎么也总得扯点跟 ObjC 相关的东西吧……

我们知道 ObjC++ 是 C++ 的超集。C++ 支持的东西他必然都支持，除此之外他还有 C++ 没有的东西，比如 block。block 可以捕获 block 中使用的外部变量，对 ObjC 的对象捕获这里就不说了，这里说下 C++ 对象的捕获。C++ 对象不支持 ObjC 的引用计数，捕获 C++ 对象也就只能靠拷贝来实现，但是 C++ 有这么多拷贝的方式，block 捕获 C++ 对象的时候使用哪种方式呢？

根据 clang 官方文档 [BlockLanguageSpec](http://clang.llvm.org/docs/BlockLanguageSpec.html) 中 "C++ Extensions" 章节对此有描述，归纳起来就是：

1. 只对栈上的 C++ 对象调用拷贝构造来捕获，引用，指针是不会拷贝的
2. 如果 C++ 对象没有__block 修饰，那么必须实现常量拷贝构造函数，否则编译出错，block 中拷贝的对象有 const 修饰
3. 如果 C++ 对象有__block 修饰，则优先调用右值拷贝构造函数，也就是说定义了右值拷贝构造函数就用右值拷贝，没有定义右值拷贝构造函数就用非常量拷贝构造函数，block 中拷贝的对象没有 const 修饰

# C++ 编译器优化之 RVO 与 NRVO

>  原文：https://www.cnblogs.com/kekec/p/11303391.html 作者：[可可西](https://home.cnblogs.com/u/kekec/) 2019-08-17 01:38

## Table of Contents

- [RVO](#rvo)
- [NRVO](#nrvo)
- [复制省略](#复制省略)
- [优化失效的情况](#优化失效的情况)
- [参考](#参考)

现代编译器缺省会使用 RVO（return value optimization，返回值优化）、NRVO（named return value optimization、命名返回值优化）和复制省略（Copy elision）技术，来减少拷贝次数来提升代码的运行效率

- 注 1：vc6、vs 没有提供编译选项来关闭该优化，无论是 debug 还是 release 都会进行 RVO 和复制省略优化
- 注 2：vc6、vs2005 以下及 vs2005+ Debug 上不支持 NRVO 优化，vs2005+ Release 支持 NRVO 优化
- 注 3：g++ 支持这三种优化，并且可通过编译选项：`-fno-elide-constructors` 来关闭优化

## RVO

```C++
#include <stdio.h>
class A {
  public:
    A() {
        printf("%p construct\n", this);
    }
    A(const A& cp) {
        printf("%p copy construct\n", this);
    }
    ~A() {
        printf("%p destruct\n", this);
    }
};

A GetA() {
    return A();
}

int main() {
    {
        A a = GetA();
    }
    return 0;
}
```

在 g++ 和 vc6、vs 中，上述代码仅仅只会调用一次构造函数和析构函数，输出结果如下：

```bash
0x7ffe9d1edd0f construct
0x7ffe9d1edd0f destruct
```

在 g++ 中，加上 - fno-elide-constructors 选项关闭优化后，输出结果如下：

```bash
0x7ffc46947d4f construct  // 在函数GetA中，调用无参构造函数A()构造出一个临时变量temp
0x7ffc46947d7f copy construct // 函数GetA return语句处，把临时变量temp做为参数传入并调用拷贝构造函数A(const A& cp)将返回值ret构造出来
0x7ffc46947d4f destruct // 函数GetA执行完return语句后，临时变量temp生命周期结束，调用其析构函数~A()
0x7ffc46947d7e copy construct // 函数GetA调用结束，返回上层main函数后，把返回值变量ret做为参数传入并调用拷贝构造函数A(const A& cp)将变量A a构造出来
0x7ffc46947d7f destruct // A a = GetA()语句结束后，返回值ret生命周期结束，调用其析构函数~A()
0x7ffc46947d7e destruct // A a要离开作用域，生命周期结束，调用其析构函数~A()
```

注：临时变量 temp、返回值 ret 均为匿名变量

下面用 c++ 代码模拟一下其优化行为：

```C++
#include <new>
A& GetA(void* p) {
    //由于p的内存是从外部传入的，函数返回后仍然有效，因此返回值可为A&
    //vs中，以下代码还可以写成:
    // A& o = *((A*)p);
    // o.A::A();
    // return o;
    return *new (p) A(); // placement new
}

int main() {
    {
        char buf[sizeof(A)];
        A& a = GetA(buf);
        a.~A();
    }

    return 0;
}
```

## NRVO

g++ 编译器、vs2005+ Release（开启 /O2 及以上优化开关）

修改上述代码，将 GetA 的实现修改成：

```C++
A GetA() {
    A o;
    return o;
}
```

在 g++、vs2005+ Release 中，上述代码也仅仅只会调用一次构造函数和析构函数 ，输出结果如下：

```bash
0x7ffe9d1edd0f construct
0x7ffe9d1edd0f destruct
```

g++ 加上 - fno-elide-constructors 选项关闭优化后，和上述结果一样

```bash
0x7ffc46947d4f construct
0x7ffc46947d7f copy construct
0x7ffc46947d4f destruct
0x7ffc46947d7e copy construct
0x7ffc46947d7f destruct
0x7ffc46947d7e destruct
```

但在 vc6、vs2005 以下、vs2005+ Debug 中，没有进行 NRVO 优化，输出结果为：

```bash
18fec4 construct  // 在函数GetA中，调用无参构造函数A()构造出一个临时变量o
18ff44 copy construct  // 函数GetA return语句处，把临时变量o做为参数传入并调用拷贝构造函数A(const A& cp)将返回值ret构造出来
18fec4 destruct  // 函数GetA执行完return语句后，临时变量o生命周期结束，调用其析构函数~A()
18ff44 destruct // A a要离开作用域，生命周期结束，调用其析构函数~A()
```

下面用 c++ 代码模拟一下 vc6、vs2005 以下、vs2005+ Debug 上的行为：

```C++
#include <new>
A& GetA(void* p) {
    A o;
    //由于p的内存是从外部传入的，函数返回后仍然有效，因此返回值可为A&
    //vs中，以下代码还可以写成:
    // A& t = *((A*)p);
    // t.A::A(o);
    // return t;
    return *new (p) A(o); // placement new
}

int main() {
    {
        char buf[sizeof(A)];
        A& a = GetA(buf);
        a.~A();
    }

    return 0;
}
```

注：与 g++、vs2005+ Release 相比，vc6、vs2005 以下、vs2005+ Debug 只优化掉了返回值到变量 a 的拷贝，命名局部变量 o 没有被优化掉，所以最后一共有 2 次构造和析构的调用

## 复制省略

典型情况是：调用构造函数进行值类型传参

```C++
void Func(A a) {}

int main() {
    {
        Func(A());
    }
    return 0;
}
```

在 g++ 和 vc6、vs 中，上述代码仅仅只会调用一次构造函数和析构函数 ，输出结果如下：

```bash
0x7ffeb5148d0f construct
0x7ffeb5148d0f destruct
```

在 g++ 中，加上 - fno-elide-constructors 选项关闭优化后，输出结果如下： 

```bash
0x7ffc53c141ef construct   // 在main函数中，调用无参构造函数构造实参变量o
0x7ffc53c141ee copy construct // 调用Func函数后，将实参变量o做为参数传入并调用拷贝构造函数A(const A& cp)将形参变量a构造出来
0x7ffc53c141ee destruct // 函数Func执行完后，形参变量a生命周期结束，调用其析构函数~A()
0x7ffc53c141ef destruct // 返回main函数后，实参变量o要离开作用域，生命周期结束，调用其析构函数~A()
```

下面用 c++ 代码模拟一下其优化行为：

```C++
void Func(const A& a) {}

int main() {
    {
        Func(A());
    }

    return 0;
}
```

## 优化失效的情况

开启 g++ 优化，得到以下各种失效情况的输出结果：

1. 根据不同的条件分支，返回不同变量

```C++
A GetA(bool bflag) {
    A a1, a2;
    if (bflag)
        return a1;
    return a2;
}

int main() {
    A a = GetA(true);

    return 0;
}
```

```bash
0x7ffc3cca324f construct
0x7ffc3cca324e construct
0x7ffc3cca327f copy construct
0x7ffc3cca324e destruct
0x7ffc3cca324f destruct
0x7ffc3cca327f destruct
```

- 注 1：2 次缺省构造函数调用：用于构造 a1、a2
- 注 2：1 次拷贝构造函数调用：用于拷贝构造返回值
- 注 3：这儿仍然用右值引用优化掉了一次拷贝函数调用：返回值赋值给 a

2. 返回参数变量
3. 返回全局变量
4. 返回复合数据类型中的成员变量
5. 返回值赋值给已构造好的变量（此时会调用 operator== 赋值运算符）

## 参考

- [Return Value Optimization](https://shaharmike.com/cpp/rvo/) 
- [What are copy elision and return value optimization?](https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization)
- [Copy elision（wiki）](https://en.wikipedia.org/wiki/Copy_elision)
- [C++ 命名返回值优化（NRVO）](https://blog.51cto.com/xdataplus/2069825)
- [Named Return Value Optimization in Visual C++ 2005](https://docs.microsoft.com/en-us/previous-versions/ms364057(v=vs.80))