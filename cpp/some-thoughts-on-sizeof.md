> @Date    : 2020-07-07 12:04:56
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 关于 sizeof() 的一些思考

- http://www.blogjava.net/majianan/archive/2006/08/20/64664.html

## 0.关键字

sizeof，字节对齐，类型大小

## 1.定义

 sizeof 是何方神圣？

    sizeof 乃 C/C++ 中的一个操作符（operator）是也。简单说其作用就是返回一个对象或者类型所占的内存字节数。

MSDN 上的解释为：

	The sizeof keyword gives the amount of storage, in bytes, associated with a variable or a type (including aggregate types). This keyword returns a value of type size_t.

其返回值类型为 size_t，在头文件 stddef.h 中定义。这是一个依赖于编译系统的值，一般定义为 typedef unsigned int size_t;

世上编译器林林总总，但作为一个规范，它们都会保证 char、signed char 和 unsigned char 的 sizeof 值为1，毕竟 char 是我们编程能用的最小数据类型。

## 2. 语法：

sizeof有三种语法形式，如下：

1. sizeof(object);     // sizeof(对象);
2. sizeof(type_name); // sizeof(类型);
3. sizeof object;      // sizeof 对象;

```c
int i;
sizeof(i);     // ok
sizeof i;      // ok
sizeof(int);   // ok
sizeof int;    // error
```


既然写法 2 可以用写法 1 代替，为求形式统一以及减少我们大脑的负担，第 2 种写法，忘掉它吧！

实际上，sizeof 计算对象的大小也是转换成对对象类型的计算。也就是说，同种类型的不同对象其 sizeof 值都是一致的。

这里，对象可以进一步延伸至表达式，即 sizeof 可以对一个表达式求值。编译器根据表达式的最终结果类型来确定大小，一般不会对表达式进行计算。

例如：

sizeof(2);        // 2 的类型为 int，所以等价于 sizeof(int);
sizeof(2 + 3.14); // 3.14 的类型为 double，2 也会被提升成 double 类型，所以等价于 sizeof(double);

sizeof 也可以对一个函数调用求值，其**结果是函数返回类型的大小，函数并不会被调用**

```c
char foo() {
	printf("foo() has been called.\n");
	return 'a';
}

int main() {
	// foo() 的返回值类型为 char，所以 sz = sizeof(char)，但函数 foo() 并不会被调用
	size_t sz = sizeof(foo());
	printf("sizeof(foo()) = %d\n", sz);
}
```

C99 标准规定，函数、不能确定类型的表达式以及位域（bit-field）成员不能被计算sizeof 值，即下面这些写法都是错误的

```c
sizeof(foo);     // error
void foo2() { }
sizeof(foo2());  // error
struct S {
	unsigned int f1 : 1;
	unsigned int f2 : 5;
	unsigned int f3 : 12;
};
sizeof(S.f1);   // error
```

【我试了下 sizeof(foo2) gcc 给出 warning，最后结果是 1】

## 3.sizeof 的常量性

sizeof 的计算发生在编译时刻，所以它可以被当作常量表达式使用。如：

char ary[sizeof(int) * 10];   // ok

最新的 C99 标准规定 sizeof 也可以在运行时刻进行计算。如下面的程序在 Dev-C++ 中可以正确执行：

```c
int n;
n = 10;        // n动态赋值
char ary[n];   // C99 也支持数组的动态定义
printf("%d\n", sizeof(ary)); // ok. 输出10
```

但在没有完全实现 C99 标准的编译器中就行不通了，上面的代码在 VC6 中就通不过编译。所以我们**最好还是认为 sizeof 是在编译期执行的**，这样不会带来错误，让程序的可移植性强些。

## 4.基本数据类型的 sizeof

这里的基本数据类型指 short、int、long、float、double 这样的简单内置数据类型。由于它们都是和系统相关的，所以在不同的系统下取值可能不同。这务必引起我们的注意，尽量不要在这方面给自己程序的移植造成麻烦。

一般的，在32位编译环境中，sizeof(int) 的取值为 4。

## 5.指针变量的 sizeof

学过数据结构的你应该知道指针是一个很重要的概念，它记录了另一个对象的地址。既然是来存放地址的，那么它当然等于计算机内部地址总线的宽度。所以在 32 位计算机中，一个指针变量的返回值必定是 4（注意结果是以字节为单位）。可以预计，在将来的 64 位系统中指针变量的 sizeof 结果为 8

```c
char* pc = "abc";
int* pi;
string* ps;
char** ppc = &pc;
void (*pf)(); // 函数指针
sizeof(pc); // 结果为4
sizeof(pi); // 结果为4
sizeof(ps); // 结果为4
sizeof(ppc);// 结果为4
sizeof(pf); // 结果为4
```

【在自己电脑上试了下，上述结果全为 8】

指针变量的 sizeof 值与指针所指的对象没有任何关系，正是由于所有的指针变量所占内存大小相等，所以 MFC 消息处理函数使用两个参数 WPARAM、LPARAM 就能传递各种复杂的消息结构（使用指向结构体的指针）

## 6.数组的 sizeof

**数组的 sizeof 值等于数组所占用的内存字节数**

```c
char a1[] = "abc";
int a2[3];
sizeof(a1); // 结果为4，字符 末尾还存在一个NULL终止符
sizeof(a2); // 结果为3*4=12（依赖于int）
```

一些朋友刚开始时把 sizeof 当作了求数组元素的个数，现在，你应该知道这是不对的。那么应该怎么求数组元素的个数呢？

Easy，通常有下面两种写法：

```c
int c1 = sizeof(a1) / sizeof(char);    // 总长度/单个元素的长度
int c2 = sizeof(a1) / sizeof(a1[0]);   // 总长度/第一个元素的长度
```

```c
// 写到这里，提一问，下面的c3，c4值应该是多少呢？
void foo3(char a3[3]) {
	int c3 = sizeof(a3); // c3 ==
	cout<<c3;
}
void foo4(char a4[]) {
	int c4 = sizeof(a4); // c4 ==
	cout<<c4;
}
```

也许当你试图回答 c4 的值时已经意识到 c3 答错了，是的，c3!=3。

这里函数参数 a3 已不再是数组类型，而是蜕变成指针。相当于 char* a3，为什么仔细想想就不难明白。

我们调用函数 foo1 时，程序会在栈上分配一个大小为 3 的数组吗？不会！

数组是“传址”的，调用者只需将实参的地址传递过去，所以 a3 自然为指针类型（char* ），c3 的值也就为 4。

## 7.string 的 sizeof

一个 string 的大小与它所指向的字符串的长度无关

```c++
string st1("blog.sina.com.cn");
string st2("majianan");
string st3;
string *ps = &st1;
cout << "st1: " << sizeof(st1) << endl;
cout << "st2: " << sizeof(st2) << endl;
cout << "st3: " << sizeof(st3) << endl;
cout << "ps: " << sizeof(ps) << endl;
cout << "*ps: " << sizeof(*ps) << endl;

// 输出结果为：
// st1： 28
// st2： 28
// st3： 28
// ps： 4
// *ps： 28
```

对于不同的 STL，String 类的结构定义会有所不同，所以不同的工具，例如 VC++，和 .NET，结果会有所不同，在 VC++6.0 中（我的机器）结果是 16，在 .NET2003 中结果是 28，但是对于同一个编译器，那么它的结果都是一定的

【在我的电脑上是 32】

## 8.引用的 sizeof

**sizeof 操作符应用在引用类型上的时候，返回的是包含被引用对象所需的内存长度（即被引用对象的大小）**

```c++
cout << "short:\t" << sizeof(short) << endl;
cout << "short*:\t" << sizeof(short*) << endl;
cout << "short&:\t" << sizeof(short&) << endl;
cout << "short[4]:\t" << sizeof(short[4]) << endl;
cout << "int&:\t" << sizeof(int&) << endl;
// 输出结果为：
// short： 2
// short*： 4
// short&： 2
// short[4]： 8
// int&： 4
```

【在我电脑上，除了第二个指针为 8，其他一样】

## 9.结构体的 sizeof

这是初学者问得最多的一个问题，所以这里有必要多费点笔墨。让我们先看一个结构体：

```c++
struct S1 {
	char c;
	int i;
};
```

聪明的你开始思考了，char占1个字节，int占4个字节，那么加起来就应该是5。

是这样吗？

你在你机器上试过了吗？

也许你是对的，但很可能你是错的！

【在我电脑上是 8】

Why？为什么受伤的总是我？

请不要沮丧，我们来好好琢磨一下 sizeof 的定义 —— sizeof 的结果等于对象或者类型所占的内存字节数。好吧，那就让我们来看看 S1 的内存分配情况：

S1 s1 = { 'a', 0xFFFFFFFF };

定义上面的变量后，加上断点，运行程序，观察s1所在的内存，你发现了什么？

以我的 VC6.0 为例，s1 的地址为 0x0012FF78，其数据内容如下：

0012FF78: 61 CC CC CC FF FF FF FF

发现了什么？怎么中间夹杂了 3 个字节的 CC？

看看MSDN上的说明：

When applied to a structure type or variable, sizeof returns the actual size, which may include padding bytes inserted for alignment.

原来如此，这就是传说中的字节对齐啊！一个重要的话题出现了。

为什么需要字节对齐？

计算机组成原理教导我们，这样有助于加快计算机的取数速度，否则就得多花指令周期了。

为此，编译器默认会对结构体进行处理（实际上其它地方的数据变量也是如此），**让宽度为2的基本数据类型（short等）都位于能被2整除的地址上，让宽度为4的基本数据类型（int等）都位于能被4整除的地址上**。以此类推，这样，两个数中间就可能需要加入填充字节，所以整个结构体的sizeof值就增长了。

让我们交换一下S1中char与int的位置：

struct S2 {
    int i;
    char c;
};

看看 sizeof(S2) 的结果为多少？怎么还是 8。

再看看内存，原来成员 c 后面仍然有 3 个填充字节。

**字节对齐的细节和编译器实现相关，但一般而言，满足三个准则**：

1. 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
2. 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节（internal adding）；
3. 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要编译器会在最末一个成员之后加上填充字节（trailing padding）。

对于上面的准则，有几点需要说明：

1. 前面不是说结构体成员的地址是其大小的整数倍，怎么又说到偏移量了呢？

因为有了第 1 点存在，所以我们就可以只考虑成员的偏移量，这样思考起来简单。想想为什么。

结构体某个成员相对于结构体首地址的偏移量可以通过宏 offsetof() 来获得，这个宏也在 stddef.h 中定义，如下：

`#define offsetof(s,m) (size_t)&(((s *)0)->m)`

例如，想要获得 S2 中 c 的偏移量，方法为

`size_t pos = offsetof(S2, c);// pos等于4`

2. 基本类型是指前面提到的像 char、short、int、float、double 这样的内置数据类型。这里所说的“数据宽度”就是指其 sizeof 的大小。由于结构体的成员可以是复合类型，比如另外一个结构体，所以在寻找最宽基本类型成员时，应当包括复合类型成员的子成员，而不是把复合成员看成是一个整体。但在确定复合类型成员的偏移位置时则是将复合类型作为整体看待。

这里叙述起来有点拗口，思考起来也有点挠头，还是让我们看看例子吧（具体数值仍以 VC6 为例，以后不再说明）：

struct S3 {
    char c1;
    S1 s;
    char c2;
};

S1 的最宽简单成员的类型为 int，S3 在考虑最宽简单类型成员时是将 S1 “打散”看的，所以 S3 的最宽简单类型为 int。这样，通过 S3 定义的变量，其存储空间首地址需要被 4 整除，整个 sizeof(S3) 的值也应该被 4 整除。

c1 的偏移量为 0，s 的偏移量呢？这时 s 是一个整体，它作为结构体变量也满足前面三个准则，所以其大小为 8，偏移量为 4，c1 与 s 之间便需要 3 个填充字节，而 c2 与 s 之间就不需要了，所以 c2 的偏移量为 12，算上 c2 的大小为 13，13 是不能被 4 整除的，这样末尾还得补上 3 个填充字节。最后得到 sizeof(S3) 的值为 16。

通过上面的叙述，我们可以得到一个公式：

**结构体的大小等于最后一个成员的偏移量加上其大小再加上末尾的填充字节数目**

`sizeof(struct) = offsetof(last item) + sizeof(last item) + sizeof(trailing padding)`

## 10.类的 sizeof

类的 sizeof 值等于类中成员变量所占用的内存字节数

```c++
class A {
 public:
     int b;
     float c;
     char d;
};

int main() {
  A object;
  cout << "sizeof(object) is " << sizeof(object) << endl;
}
```

输出结果为 12（我的机器上 sizeof(float)值为 4，字节对齐前面已经讲过）

不过需要注意的是，如果类中存在静态成员变量，结果又会是什么样子呢？

```c++
class A {
 public:
     static int a;
     int b;
     float c;
     char d;
};

int main() {
  A object;
  cout << "sizeof(object) is " << sizeof(object) << endl;
}
```

16？不对。结果仍然是 12.

因为在程序编译期间，就已经为 static 变量在静态存储区域分配了内存空间，并且这块内存在程序的整个运行期间都存在。

而每次声明了类 A 的一个对象的时候，为该对象在堆上，根据对象的大小分配内存。
 
如果类 A 中包含成员函数，那么又会是怎样的情况呢？看下面的例子

```c++
class A {
 public:
     static int a;
     int b;
     float c;
     char d;
     int add(int x,int y) {
       return x+y;
     }
};

int main() {
  A object;
  cout << "sizeof(object) is " << sizeof(object) << endl;
  b = object.add(3,4);
  cout << "sizeof(object) is " << sizeof(object) << endl;
  return 0 ;
}
```

结果仍为 12

因为只有非静态类成员变量在新生成一个 object 的时候才需要自己的副本。

所以每个非静态成员变量在生成新 object 需要内存，而 function 是不需要的。

注：C++中的多态和虚继承也是非常重要的东西，不过比较复杂，编译器不同，细节也有所不同。（以后慢慢研究，哈哈）