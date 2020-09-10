> @Date    : 2020-09-10 19:45:16
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# C++ 的返回值优化以及右值拷贝

很有趣的一个问题，当一个函数返回一个局部变量，会发生几次拷贝呢？

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [sq.163yun.com](https://sq.163yun.com/blog/article/170332301127245824) [达芬奇密码](https://sq.163yun.com/user/165240397716357120) 2018-06-27 15:49

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
