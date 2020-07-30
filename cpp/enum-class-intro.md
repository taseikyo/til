> @Date    : 2020-07-30 16:28:43
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/xuanwolanxue/article/details/79801038)

# 奇妙的 enum class，enum struct 组合

1. 传说中的 enum 关键字
----------------

不管是 c 语言，还是 c++ 语言， 其中都有 enum 关键字。这是这两种语言的基础知识中都会涉及到的点。

其具体定义方法如下：

```c++
enum my_enum {
    my_enum1 = 0,
    my_enum2,
};
```

当然也可以省略 enum 的名字，使用匿名的方式定义枚举，如下所示：

```c++
enum {
    my_enum1 = 0,
    my_enum2,
};
```

或者与 ‘typedef’ 关键字联合使用，如：

```c++
typedef enum {
    my_enum1 = 0,
    my_enum2,
}my_enum;
```

2. 传统 enum 关键字存在的问题
-------------------

*   全局作用域

传统的 enum 关键字的作用域是全局的，也就是说，如果在 enum A 中声明的一个枚举类型 my_enum3，无法在 enum B 中声明同样的枚举类型，具体的就是，如下的写法是错误的，会出现编译错误 (会报 重定义错误)

```c++
enum A {
    my_enum3 = 0,
};

enum B {
    my_enum3 = 0,
};
```

*   能隐式转换为其他类型 (如整型)

具体如下面的代码所示：

```c++
enum my_enum {
    my_enum1 = 0,
    my_enum2,

};

int my_int = my_enum1;
```

*   无法指定底层使用的数据类型

也就是说，无法明确的知道，一个枚举类型，占用内存的字节数，这样在结构体中使用 enum 的时候就可能遇到麻烦， 特别是结构体需要内存对齐或者填充处理的时候问题就尤为突出了。

3. 奇妙的 enum class，enum struct 组合
--------------------------------

在 c++11 标准中，除了传统的 enum 关键字之外， 还新增了一个概念： enum class， enum struct 组合的形式 (两者是等价的)，当然单纯的 enum 关键字和 enum class 组合并不冲突，都能使用。 这一组合的出现就是为了解决传统 enum 关键字面临的问题。

*   enum class 组合具有 class 封装性的特性，作用域是确定的

```c++
enum class A {
    my_enum3 = 0,
};

enum class B {
    my_enum3 = 0,
};

enum C {
    my_enum3 = 0,
};
```

如上面这样声明和定义枚举就是正确的，要访问 A 和 B 中的枚举是需要加上作用域的，形如：

```c++
A a = A::my_enum3;
B b = B::my_enum3;
```

*   可以指定底层数据类型

```c++
enum class A: int /** 每个枚举都是int类型的 */
{
    my_enum3 = 0,
};

enum class B: unsigned char /** 每个枚举都是unsigned char类型的 */
{
    my_enum3 = 0,
};
```

*   不能隐式转换

```c++
int my_int = A::my_enum3; /** 错误，无法通过编译 */


int my_int = static_cast<int>(A::my_enum3); /** 正确， 可以通过编译 */
```

4. 总结
-----

enum class， enum struct 组合的出现可以极大的增加枚举类型使用的灵活性，安全性以及易用性。

比如，在项目中枚举较多的时候，为了区分，往往会将 每个枚举的长度， 比如 A_MODULE_B_TYPE_C 等等， 如果使用 enum class 组合的话，只需要在定义如下定义：

```c++
enum class AModuleBType: uint8_t {
    c = 0,
};

AModuleBType type = AModuleBType::c; /** 具体使用形式 */
```

这样在枚举中就只需要关注枚举代表的内容，不需要去区分前缀或是否重定义等问题。

说实话，笔者也是最近才知道有 enum class 这样的组合方式， 了解之后有种如获至宝的感觉。 这里并不是说 enum class 有多么多么好。 而是说明在技术这条道路上学无止境。 不停的学习，虽然不一定能让你变得多厉害，多牛叉，但它至少能在一定程度上保证自己不会倒退，不会太快的被历史的巨轮碾压而淘汰。