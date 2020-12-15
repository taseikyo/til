> @Date    : 2020-06-23 11:43:36
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

## C++ STL 容器

- https://www.jianshu.com/p/497843e403b4
- https://www.cnblogs.com/linuxAndMcu/p/10254542.html
- https://www.cnblogs.com/yinheyi/p/7504041.html

STL (标准模板库)，是目前 C++ 内置支持的 library。它的底层利用了 C++ 类模板和函数模板的机制，由三大部分组成：容器、算法和迭代器。

目前 STL 有六大组件

- 容器 container
- 算法 algorthm
- 迭代器 iterator
- 仿函数 function object
- 适配器 adaptor
- 空间配置器 allocator

下面，我们会一一进行介绍。

## Table of Contents
- [STL 初探](#stl-初探)
- [STL 中的 string](#stl-中的-string)
	- [string 的构造函数](#string-的构造函数)
	- [字符串的遍历](#字符串的遍历)
	- [string 与 char \* 的转换](#string-与-char--的转换)
	- [string 的拼接](#string-的拼接)
	- [string 的查找和替换](#string-的查找和替换)
	- [string 区间删除和插入](#string-区间删除和插入)
	- [string 算法相关](#string-算法相关)
- [STL 中的 vector 容器](#stl-中的-vector-容器)
	- [vector 的基本用法](#vector-的基本用法)
	- [vector 的初始化](#vector-的初始化)
	- [vector 的遍历](#vector-的遍历)
	- [vector 的 push\_back 强化](#vector-的-push_back-强化)
	- [vector 的元素删除](#vector-的元素删除)
	- [vector 的插入元素](#vector-的插入元素)
- [STL 中的 deque 容器](#stl-中的-deque-容器)
- [STL 中的 stack 栈容器](#stl-中的-stack-栈容器)
- [STL 中的 queue 队列容器](#stl-中的-queue-队列容器)
- [STL 中的 list 容器](#stl-中的-list-容器)
	- [list 的基本操作](#list-的基本操作)
	- [list 的删除](#list-的删除)
- [STL 中的 priority\_queue 优先级队列容器](#stl-中的-priority_queue-优先级队列容器)
- [STL 中的 set 和 multiset 集合容器](#stl-中的-set-和-multiset-集合容器)
	- [set 元素的插入和删除](#set-元素的插入和删除)
	- [普通数据类型的排序](#普通数据类型的排序)
	- [自定义对象的排序](#自定义对象的排序)
	- [pair 类型的返回值](#pair-类型的返回值)
	- [set 容器数据的查找](#set-容器数据的查找)
	- [multiset 容器](#multiset-容器)
- [STL 中的 map 和 multimap 映射容器](#stl-中的-map-和-multimap-映射容器)
	- [map 元素的增删改查](#map-元素的增删改查)
	- [map 元素的查找](#map-元素的查找)
	- [multimap 容器](#multimap-容器)
- [STL 容器的通用性探究](#stl-容器的通用性探究)
	- [STL 容器的元素拷贝](#stl-容器的元素拷贝)
	- [STL 容器的比较](#stl-容器的比较)
    - [各容器的时间复杂度分析](#各容器的时间复杂度分析)

### STL 初探

容器是 STL 中很重要的一种数据结构。容器分类：

- 顺序容器：
    - vector
    - string (它不是类模板）
    - list 双向链表
    - forward_list 单向链表
    - deque
    - queue
    - priority_queue
    - stack
- 有序关联容器：
    - map
    - multimap
    - set
    - multiset
- 无序关联容器：
    - unordered_map
    - unordered_multimap
    - unordered_set
    - unordered_multiset

除了容器，STL 还封装了强大的算法，能够实现查找、删除、替换、删除等很多常见操作。后面会重点讲解。

另外，迭代器也是 STL 重要的一环，通过迭代器，我们可以很方便对容器中的元素进行遍历，以及操作容器。后面我们会穿插讲解迭代器。

### STL 中的 string

`string` 是 STL 的字符串类型，在 C 语言中，我们通常用 `char *` 或者 `char []` 字符数组来表示字符串。C++ 的 `string` 和 C 语言的 `char *` 有什么区别呢？

- `string` 是一个类，`char *` 是指向字符的指针
- `string` 封装了 `char *`, 管理这个字符串，是一个 `char *` 类型的容器
- `string` 不用考虑内存释放和数组越界
- `string` 提供了一些列的字符串操作函数

#### string 的构造函数

既然 string 是一个类，那么也就有构造函数，我们研究下 string 的构造函数。

```c++
#include <iostream>
using namespace std;
int main(int argc, const char * argv []) {
    
    // 通过 const char * 初始化
    string s1 = "aaaa";
    
    // 构造函数初始化
    string s2 ("bbbbb");
    
    // 通过拷贝构造函数来初始化对象 s3
    string s3 = s2;
    
    // 用 10 个 'a' 字符来初始化字符串
    string s4 (10, 'a');
    
    return 0;
}
```

#### 字符串的遍历

字符串的遍历，有三种遍历的方式

- 数组方式遍历，通过 \[\] 操作符遍历 （不会抛出异常）
- at() 方法遍历，根据 index 取值 (会抛出异常)
- 通过 STL 迭代器遍历

```c++
int main(int argc, const char * argv []) {
    
    // 创建字符串对象
    string str("abcdefg");
    
    // 数组形式遍历
    for(int i = 0; i < str.length(); i++) {cout<< str [i] <<endl;}
    
    //at 方法遍历
    for(int i = 0; i < str.length(); i++) {cout << str.at(i) <<endl;}
    
    // 迭代器遍历
    for(string::iterator it = str.begin(); it != str.end(); it++) {cout << *it << endl;}

    return 0;
}
```

数组方式和 at 方法方式，有一个明显的不同

- 数组方式，如果出现越界或者其他错误，不会抛出异常，程序直接终端。
- at() 方法遍历，出现越界或其他错误，会抛出异常，程序可以处理异常。

迭代器其实可以看作是一个字符的指针，上个例子中 `string::iterator it = str.begin()` 就是定义一个 string 类型的迭代器，指向 `str` 的第一次位置。`*it` 就表示当前的字符。注意 `str.end()` 表示字符串最后一个字符的后面一个位置。如果 `it == str.end()` 就表示已经遍历到终点了。

#### string 与 char \* 的转换

string 提供了成员函数 `c_str` 来将 string 对象转化成 `const char *`。string 提供了 `copy(buf,size,begin)` 成员函数来讲 string 从 `begin` 位置开始的 `size` 个字符拷贝到 `buf` 中。需要注意的是:

- 如果 buf 容纳不下，会越界
- 拷贝过去后，不会转变成 C 风格的字符串，也就是不会在 buf 后面添加 \'\\0\'

```c++
int main(int argc, const char * argv []) {
    
    //1 string 转 char *
    string str("aaaaaa");
    const char *p = str.c_str();
    
    //2 char * 转 string
    const char *p1 = "12345";
    string str2 = p1;
    
    //3 string 拷贝到 buf [] 中
    char buf [128] = {0};
    // 从 0 开始，拷贝 3 个字符到 buf 指向的内存空间
    // 如果 buf 空间容纳不下，会越界
    // 拷贝过去时，不会给 buf 末尾添加 \0
    str.copy(buf, 3, 0);

    return 0;
}
```

#### string 的拼接

string 为我们提供了两种字符串拼接方式，一种是重写了 `+`
操作符，我们可以直接将连个字符串相加，类似于 java 的语法。另一种是 string 提供了成员函数 `append()` 供我们拼接连个字符串.

```c++
int main(int argc, const char * argv []) {
    
    string s1 = "123456";
    string s2 = "abcdef";
    
    // 直接使用加号运算符拼接
    string s3 = s1 + s2;
    
    // 使用成员函数拼接
    string s4 = s1.append(s2);
    
    cout<<s3<<endl;
    cout<<s4<<endl;
    
    return 0;
}
```

#### string 的查找和替换

string 类提供了 `find` 函数，用来查找字符串中指定的字符。提供了 `replace` 函数，用来替换字符串中指定位置的字符串。

`replace` 函数是，先删除指定位置，指定长度的字符，然后在当前指定位置插入新的字符。

```c++
int main(int argc, const char * argv []) {
    
    
    string s1 = "hello hello hello hello hello hello 1234 7876";
    
    // 从 0 位置开始查找第一个 hello 出现的首位位置
    size_t index1 = s1.find("hello",0);
    cout << index1 << endl;
    
    // 查找第一个 hello 出现时的首位位置
    size_t index2 = s1.find_first_of("hello");
    cout << index2 << endl;
    
    // 查找最后一个 hello 出现时的末尾位置
    size_t index3 = s1.find_last_of("hello");
    cout << index3 << endl;
    
    // 求 hello 出现的次数，以及对应的下标
    int count = 0;
    size_t offindex = s1.find("hello",0);
    while(offindex != string::npos) {  // 如果 offindex != -1
        // 找到了
        cout << "索引:" << offindex <<endl;
        count++;
        offindex++;
        offindex = s1.find("hello", offindex);
    }
    
    // 把 hello 替换成 welcome
    size_t offindex1 = s1.find("hello", 0);
    while(offindex1 != string::npos) {
        
        // 从 offindex1 的位置开始删除 5 个位置，并插入新的字符串 welcome
        s1.replace(offindex1, strlen("hello"), "welcome");
        
        // 从后面的位置开始
        offindex1 += strlen("welcome");
        
        // 继续查找
        offindex1 = s1.find("hello", offindex1);
    }
    cout << "替换后的字符串：" << s1 <<endl;

    return 0;
}
```

#### string 区间删除和插入

string 提供了 `insert` 和 `erase` 分别实现插入和删除操作。

插入：pos 位置插入字符串 s，返回新的 string。

- `string &insert(int pos, const char *s)`
- `string &insert(int pos, const string &s)`

插入：pos 位置插入 n 个字符 c，返回 string。

- `string &insert(int pos, int n, char c)`

删除：删除从 pos 位置开始的 n 个字符，返回新的 string

- `string &erase(int pos, int n)`

删除：删除指定迭代器的位置，返回当前迭代器位置

- `string::iterator erase(string::iterator it)`

删除：删除迭代器之间的字符，左闭右开区间

- `string::iterator erase(string::iterator beginIt, string::iterator endIt)`

```c++
int main(int argc, const char * argv []) {
    
    string s1 = "hello1 world!";
    
    //1 删除字符串中的 '1'
    //--- 通过 find 函数，查找 '1' 所在的迭代器位置
    string::iterator it = find(s1.begin(), s1.end(), '1');
    //--- 删除
    if(it != s1.end()) {
        s1.erase(it);
    }
    cout << s1 << endl;
    
    //2 删除起始迭代器位置的字符
    s1.erase(s1.begin(), s1.begin() + 3);
    cout << s1 << endl;
    
    //3 在 0 位置插入 "AAA"
    s1.insert(0, "AAA");
    cout << s1 << endl;
    
    return 0;
}
```

#### string 算法相关

目前常见的 string 的算法是大小写转换。一般使用函数 `transform` 来进行转换。

文章中没写 `transform` 用法，查了一下，包含着 `algorithm` 头文件中，如下所示

```c++
// std::transform 用法
transform（_InputIterator __first, _InputIterator __last, _OutputIterator __result, _UnaryOperation __op）
```

```c++
int main(int argc, const char * argv []) {
    
    string s1 = "abcdefg";
    string s2 = "AEDLFLKJDLKJFL";
    
    // 小写全部转换成大写，转换的结果放在 s1.begin() 的位置，后面的操作需要强制转换成指定的函数类型
    transform(s1.begin(), s1.end(), s1.begin(), (int(*)(int)) toupper);
    cout << s1 <<endl;
    
    // 大写全部转换成小写
    transform(s2.begin(), s2.end(), s2.begin(), (int(*)(int)) tolower);
    cout << s2 <<endl;
   
    return 0;
}
```

### STL 中的 vector 容器

`vector` 是将元素放到动态数组中加以管理的容器。`vector` 容器可以随机存取元素，也就是说支持 `[]` 运算符和 `at` 方式存取。

- `vector` 在尾部添加或者移除元素非常快，在中间操作非常耗时，因为它需要移动元素

#### vector 的基本用法

既然 vector 是容器，那么就可以向这个容器添加删除元素。

基本用法：

- `front()` 返回头部元素的引用，可以当左值
- `back()` 返回尾部元素的引用，可以当左值
- `push_back()` 添加元素，只能尾部添加
- `pop_back()` 移除元素，只能在尾部移除

```c++
int main(int argc, const char * argv []) {
    
    // 定义一个 vector 容器
    vector<int> v1;
    
    // 插入元素 (尾部插入)
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    
    // 迭代器遍历打印
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    // 修改头部元素的值 (front() 返回是引用，可以当左值)
    v1.front() = 44;
    
    // 输出头部元素
    cout<<"头部元素:" << v1.front() << endl;
    
    // 修改尾部的值 (back() 返回是引用，可以当左值)
    v1.back() = 99;
    
    // 输出尾部元素
    cout <<"尾部元素" << v1.back() <<endl;
    
    // 删除元素 (从尾部删除)
    v1.pop_back();
    
    // 迭代器遍历打印
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

#### vector 的初始化

vector 有 4 种方式初始化，有直接初始化，也要通过拷贝构造函数初始化。

```c++
int main(int argc, const char * argv []) {

    // 直接构造函数初始化
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    
    // 通过拷贝构造函数初始化
    vector<int> v2 = v1;
    
    // 使用部分元素来构造
    vector<int> v3 (v1.begin(), v1.begin() + 1);
    vector<int> v4 (v1.begin(), v1.end());
    
    // 存放三个元素，每个元素都是 9
    vector<int> v5 (3,9);
    
    return 0;
}
```

#### vector 的遍历

vector 的遍历有多种方式，可以根据 `[]` 或者迭代器遍历。

需要主要的是：

- `[]` 方式，如果越界或出现其他错误，不会抛出异常，可能会崩溃，可能数据随机出现
- `at` 方式，如果越界或出现其他错误，会抛出异常，需要捕获异常并处理
- 迭代器提供了逆向遍历，可以通过迭代器来实现逆向遍历，当然上面两种方式也可以

```c++
int main(int argc, const char * argv []) {
    
    // 创建 vector
    vector<int> v1;
    
    // 插入元素
    for(int i = 0; i < 10; i++) { v1.push_back(i); }
    
    // 遍历 -[] 取值
    for(int i = 0; i < v1.size(); i++) {cout << v1 [i] <<" ";}
    cout << endl;
   
    // 遍历 - at 取值
    for(int i = 0; i < v1.size(); i++) {cout << v1.at(i) <<" ";}
    cout << endl;

    // 遍历 - 迭代器遍历
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    // 遍历 - 迭代器逆向遍历
    for(vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++) {cout << *it << " ";}
    cout << endl;
    
    // 测试越界
    cout <<"[] 越界:" <<v1 [20] << endl;      // 不会抛出异常，可能会崩溃，可能会乱码
    cout <<"at 越界:" << v1.at(20) << endl;   // 会抛出异常，需要捕获异常
    
    return 0;
}
```

#### vector 的 push\_back 强化

push\_back 是在当前 vector 的内存末尾拷贝元素进入容器。注意这个地方可能产生浅拷贝，所以容器中的对象要支持拷贝操作。另外，如果 vector 初始化了个数，而不初始化具体的值，push\_back 也只会在最后面追加。

```c++
int main(int argc, const char * argv []) {
    
    // 初始化 10 个元素的容器
    vector<int> v(10);
    
    // 打印容器大小
    cout <<v.size() << endl;
    
    //push_back 添加元素
    v.push_back(100);
    
    // 打印容器大小
    cout <<v.size() << endl;
    
    // 遍历后的结果是  0 0 0 0 0 0 0 0 0 0 100
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

#### vector 的元素删除

vector 的删除，是根据位置进行删除，如果想要删除某个元素，需要找到当前元素的迭代器位置，再进行删除。

> `erase(iterator)` 函数，删除后会返回当前迭代器的下一个位置。

```c++
int main(int argc, const char * argv []) {
    
    //1 创建容器并初始化
    vector<int> v1 (10);
    for(int i = 0; i < v1.size(); i++) {v1 [i] = i;
    }
    
    //2 区间删除
    //--2.1 删除前 3 个元素
    v1.erase(v1.begin(), v1.begin() + 3);
    
    //--2.2 删除指定位置的元素
    v1.erase(v1.begin() +3);
    
    //3 根据元素的值进行删除，删除值为 2 的元素
    v1.push_back(2);
    v1.push_back(2);
    vector<int>::iterator it = v1.begin();
    while(it != v1.end()) {
        if(*it == 2) {
            it = v1.erase(it);   // 删除后，迭代器指针会执行下一个位置并返回。
        } else {
            it++;
        }
    }
    
    //4 遍历打印
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

#### vector 的插入元素

vector 提供了 `insert` 函数，结合迭代器位置插入指定的元素。

如果迭代器位置越界，会抛出异常。

```c++
int main(int argc, const char * argv []) {
    
    // 初始化 vector 对象
    vector<int> v1 (10);
    
    // 在指定的位置插入元素 10 的拷贝
    v1.insert(v1.begin() + 3, 10);
    
    // 在指定的位置插入 3 个元素 11 的拷贝
    v1.insert(v1.begin(), 3, 11);
    
    // 遍历
    for(vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

### STL 中的 deque 容器

deque 是一个双端数组容器：可以在头部和尾部操作元素。

- `push_back` 从尾部插入元素
- `push_front` 从头部插入元素
- `pop_back` 从尾部删除元素
- `pop_front` 从头部删除元素

> 知识点：
>
> `distance` 函数可以求出当前的迭代器指针 it 距离头部的位置，也就是容器的指针
>
> 用法: `distance(v1.begin(), it)`

```c++
int main(int argc, const char * argv []) {
    
    // 定义 deque 对象
    deque<int> d1;
    
    // 尾部插入元素
    d1.push_back(10);
    d1.push_back(20);
    d1.push_back(30);
    
    // 头部插入元素
    d1.push_front(1);
    d1.push_front(2);
    d1.push_front(3);
    
    // 尾部删除元素
    d1.pop_back();
    
    // 头部删除元素
    d1.pop_front();
    
    // 修改头部和尾部的值
    d1.front() = 111;
    d1.back()  = 222;
    
    // 查找元素为 1 的下标
    // 通过 distance 求取下标
    deque<int>::iterator it = d1.begin();
    while(it != d1.end()) {if(*it == 1) {cout << "下标：" << distance(d1.begin(), it) <<endl;}
        it++;
    }
    
    // 遍历
    for(deque<int>::iterator it = d1.begin(); it != d1.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

### STL 中的 stack 栈容器

在数据结构中，栈是一种先入后出的容器，增加元素叫压栈或者入栈。移除元素通常叫做出栈。

STL 提供的 stack 容器，也是这种基本类型。这里我们演示一下基本元素类型和复杂元素类型。

▽ 基础数据类型的 stack

```c++
int main(int argc, const char * argv []) {
    
    // 定义 stack 对象
    stack<int> s1;
    
    // 入栈
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    
    // 打印栈顶元素，并出栈
    while(!s1.empty()) {
        // 取出栈顶元素
        cout <<"当前栈顶元素" << s1.top() << endl;
        
        // 获取栈的大小
        cout <<"当前栈的大小" << s1.size() << endl;
        
        // 出栈
        s1.pop();}
    
    return 0;
}
```

▽ 复杂数据类型的 stack

```c++
// 定义类
class Teacher {
    
public:
    
    char name [32];
    int  age;
    
    void printT() {
        cout << "age =" << age << endl;
    }
    
};

int main(int argc, const char * argv []) {
    
    Teacher t1, t2, t3;
    t1.age = 22;
    t2.age = 33;
    t3.age = 44;
    
    // 定义栈容器
    stack<Teacher> s1;
    
    // 入栈
    s1.push(t1);
    s1.push(t2);
    s1.push(t3);
    
    // 出栈并打印
    while(!s1.empty()) {
        // 打印栈顶元素
        Teacher tmp = s1.top();
        tmp.printT();
        
        // 出栈
        s1.pop();}

    return 0;
}
```

### STL 中的 queue 队列容器

队列是一种数据结构，具备队头和队尾。常见的有 FIFO（先入先出）队列等。

```c++
#include <queue>

int main(int argc, const char * argv []) {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    cout <<"对头元素" << q.front() <<endl;
    cout <<"队列的大小" << q.size() <<endl;
    
    while(!q.empty()){
        int tmp = q.front();
        cout << tmp << " ";
        q.pop();
    }

    return 0;
}



class Teacher
{
public：
    int age;
    char name [32];
    
    void printT()
    {cout << "age ：" << age <<endl;}
}

int main(int argc, const char * argv []) {
    Teacher t1,t2,t3;
    t1.age = 31;
    t2.age = 32;
    t3.age = 33;
    
    queue<Teacher> q;
    q.push(t1);
    q.push(t2);
    q.push(t3);
    
    while(!q.empty()){
        Teacher tmp = q.front();
        tmp.printT();
        q.pop();
    }

    return 0;    
}
```

### STL 中的 list 容器

list 容器具有如下特性：

- 可以在头部和尾部插入和删除元素
- 不能随机访问元素，也就是迭代器只能只能 ++, 不能一次性跳转

#### list 的基本操作

```c++
int main(int argc, const char * argv []) {
    
    // 创建 list 对象
    list<int> l;
    
    // 尾部添加元素
    for(int i = 0; i < 10; i++) {l.push_back(i);}
    
    // 头部添加元素
    l.push_front(111);
    
    // 遍历
    for(list<int>::iterator it = l.begin(); it != l.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    //list 不能随机访问
    list<int>::iterator it = l.begin();
    it++;
    it++;
    cout << *it <<endl;
//    it = it + 1;  // 编译报错，不能随机访问
//    it = it + 5;  // 编译报错，不能随机访问
    
    
    return 0;
}
```

#### list 的删除

list 提供了两个函数用来删除元素，分别是 `erase` 和 `remove`。

- `erase` 是通过位置或者区间来删除，主要结合迭代器指针来操作
- `remove` 是通过值来删除

```c++
int main(int argc, const char * argv []) {
    
    // 创建 list 对象
    list<int> l;
    
    // 添加数据
    for(int i = 0; i < 10; i++) {l.push_back(i);}
    l.push_back(100);
    l.push_back(100);
    
    // 删除头部元素
    l.erase(l.begin());
    
    // 删除某个区间
    list<int>::iterator it = l.begin();
    it++;
    it++;
    it++;
    l.erase(l.begin(), it);
    
    // 移除值为 100 的所有元素
    l.remove(100);
    
    // 遍历
    for(list<int>::iterator it = l.begin(); it != l.end(); it++) {cout << *it << " ";}
    cout << endl;
    
    return 0;
}
```

### STL 中的 priority\_queue 优先级队列容器

优先级队列分为：最小值优先队列和最大值优先队列。

此处的最大值、最小值是指队头的元素（增序、降序）。默认，是创建最大值优先级队列。

定义优先级的方法：

- `priority_queue<int>` 默认定义 int 类型的最大值队列
- `priority_queue<int, vector<int>, less<int>>` 定义 int 型的最大值优先队列
- `priority_queue<int, vector<int>, greater<int>>` 定义 int 型的最小值队列

上面的定义中，`less` 和 `greater` 相当于谓词，是预定义好的排序函数，我们称之为 "仿函数"。后面会介绍它的用法。

```c++
int main(int argc, const char * argv []) {
    // 定义优先级队列 (默认是最大值优先级队列)
    priority_queue<int> p1;
    
    // 定义一个最大优先级队列
    //less 是提前定义好的预定义函数 相当于谓词
    priority_queue<int, vector<int>, less<int>> p2;
    
    // 定义一个最小值优先级队列 v
    priority_queue<int, vector<int>, greater<int>> p3;
    
    // 给默认的最大优先级队列入栈
    p1.push(33);
    p1.push(11);
    p1.push(55);
    p1.push(22);
    
    // 打印最大优先级的对头元素
    cout<<"对头元素:"<< p1.top() <<endl;
    cout<<"队列的大小:"<< p1.size() <<endl;
    
    // 给最小值优先级队列入栈
    p3.push(33);
    p3.push(11);
    p3.push(55);
    p3.push(22);
    
    // 打印最小优先级队列的对头元素
    cout<<"对头元素:"<< p3.top() <<endl;
    cout<<"队列的大小:"<< p3.size() <<endl;}
```

### STL 中的 set 和 multiset 集合容器

set 是一个集合，`Objective-C` 语言中也有集合的概念。C++ 中的集合与 OC 中的集合也有不同的地方。

- C++ 的 set 容器，其中包含的元素是唯一的，而且是有序的。
- C++ 的 set 容器，是按照顺序插入的，不能在指定位置插入。
- C++ 的 set 容器，其结构是红黑二叉树，插入数据的效率比 vector 快

#### set 元素的插入和删除

set 提供了 `insert` 和 `erase` 函数，用来对元素进行插入和删除操作。

- 基础类型数据，如果插入的是重复的元素，则插入失败，返回值是一个 pair 类型
- pair 类型类似于 swift 语言中的元组的概念，通过其判断是否插入成功
- 复杂类型数据，需要通过仿函数来确定元素的顺序，进入判断是否是重复元素。在 "自定义对象的排序" 里面讲解。

```c++
int main(int argc, const char * argv []) {
    set<int> set1;
    
    // 插入元素
    for(int i = 0; i<5; i++) {
        int tmp = rand();
        set1.insert(tmp);
    }
    
    // 重复插入元素（会插入不成功，下一节会分析如果根据返回值判断是否插入成功）
    set1.insert(100);
    set1.insert(100);
    set1.insert(100);
    set1.insert(100);
    
    for(set<int>::iterator it = set1.begin(); it != set1.end(); it++) {cout << *it <<" ";}
    
    
    // 删除集合
    while(!set1.empty()) {
        // 获取头部
        set<int>::iterator it = set1.begin();
        
        // 打印头部元素
        cout << *it << endl;
        
        // 从头部删除元素
        set1.erase(set1.begin());
    }
    
    return 0;
}
```

#### 普通数据类型的排序

set 容器是有序的集合，默认的顺序是从小到大的。

创建集合的方式：

- `set<int>` 创建默认的从小到大的 int 类型的集合
- `set<int,less<int>>` 创建一个从小打到大的 int 类型的集合
- `set<int,greater<int>>` 创建一个从大到小的 int 类型的集合

上面的 less 和 greater 就是仿函数，集合会根据这个仿函数的返回值是否为真类进行排序。

```c++
// 仿函数的原型，下面是 C++ 提供的默认的 greater 的仿函数 (删除了宏定义后的)
struct greater {
    bool operator()(const int &left, const int &right) const {
        // 如果左值 > 右值，为真。从大到小的排列
        return left > right;
    }
};
```

我们可以测试下，添加进 set 集合的元素确实是有顺的。

```c++
int main(int argc, const char * argv []) {
    // 默认，从小到大
    set<int> set1;
    // 从小到大 -- 默认就是
    set<int, less<int>> set2;
    // 从大到小
    set<int, greater<int>> set3;

    // 添加元素
    for(int i = 0; i < 5; i++) {int tmp = rand();
        set3.insert(tmp);
    }
    
    // 遍历
    for(set<int>::iterator it = set3.begin(); it != set3.end(); it++) {cout<< *it << " ";}

    return 0;
}
```

#### 自定义对象的排序

上面，我们看到了基础的数据类型的集合，是可以排序的。但是，如果集合里面放的是特殊的自定义对象，该如何满足 set 有序的特性呢？

通过上面的例子，我们知道，基础数据类型的 set 是有序的关键原因是 greater 和 less 仿函数。所以，自定义对象的有序也是通过我们自定义仿函数来保证的。

仿函数，之所以叫仿函数，是因为它跟函数很像，但并不是一个函数。它的结果如下，只要我们实现了这个仿函数，我们也可以对自定义对象进行排序。

```c++
// 定义仿函数的结构体
struct FunctionName
{// 重载了() 运算符，实现两个自定义对象的比较
    bool opeartor() (Type &left, Type &right)
    {
        // 左值大于右值，从大到小的顺序
        if(left> right) 
            return true;
        else
            return false;
        
    }
};
```

下面，我们自定义一个 Student 对象，根据年龄进行排序，将对象加入到 set 集合中，并进行打印。

> 如果仿函数实现了根据年龄进行排序，因为 set 是元素唯一的，所以在插入对象的时候，如果年龄是重复的，则插入不进去了。

```c++
// 定义 student 对象
class Student {
public:
    Student(const char *name, int age) {
        strcpy(this->name, name);
        this->age = age;
    }
    
public:
    char name [64];
    int  age;
};

// 提供仿函数，用于自定义对象的 set 进行排序，要写一个仿函数，用来排序
struct FuncStudent {
    // 重载了括号操作符，用来比较大小
    bool operator() (const Student &left, const Student &right) {
        // 如果左边比右边小，从小到大按照年龄排序
        if(left.age < right.age)
            return true;
        else
            return false;
    }
    
};

void main() {
    Student s1 ("s1",32);
    Student s2 ("s2",22);
    Student s3 ("s3",44);
    Student s4 ("s4",11);
    Student s5 ("s5",22); 
    
    // 创建集合，采用从小到大的排序
    set<Student, FuncStudent> set1;
    
    // 插入数据
    set1.insert(s1);
    set1.insert(s2);
    set1.insert(s3);
    set1.insert(s4);
    // 插入不进去 (年龄有重复的，所以插不进去了), 要通过返回值来确保是否插入成功
    set1.insert(s5);    
    
    // 遍历
    for(set<Student>::iterator it = set1.begin(); it != set1.end(); it++) {cout << it->age <<"\t" << it->name <<endl;}
    
}
```

#### pair 类型的返回值

pair 类型，就类似于 Swift 语言中的 "元组" 的概念，这个类型包含了多个数据类型，在函数返回的时候，可以同时返回多个值。

我们来看一下 pair 类型的定义它实际上是一个结构体。它包含了两个属性，`first` 和 `second`。

```c++
template <class _T1, class _T2>
struct pair {
    typedef _T1 first_type;
    typedef _T2 second_type;

    _T1 first;
    _T2 second;
}
```

上面的例子中，我们知道 set 集合中的元素是唯一的，重复的元素插入会失败。如果判断是否插入成功，我们可以通过 `insert`函数的返回值来判断，它的返回值是一个 `pair` 类型。我们来看一下 `insert` 函数的原型:

```c++
pair<iterator,bool> insert(const value_type& __v)
```

返回的是 `pair<iterator, bool>` 类型，pair 的第一个属性表示当前插入的迭代器的位置，第二个属性表示插入是否成功的 bool 值。所以，我们可以通过第二个属性来判断元素是否插入成功。

```c++
//pair 的使用判断 set 的 insert 函数的返回值
void test3() {
    Student s1 ("s1",32);
    Student s2 ("s2",22);
    Student s3 ("s3",44);
    Student s4 ("s4",11);
    Student s5 ("s5",22);
    
    // 创建集合，采用从小到大的排序
    set<Student, FuncStudent> set1;

    // 插入数据，接收返回值
    pair<set<Student, FuncStudent>::iterator, bool> pair1 = set1.insert(s1);
    if(pair1.second == true) {cout << "插入 s1 成功" <<endl;} else {cout << "插入 s1 失败" <<endl;}
}
```

#### set 容器数据的查找

set 容器提供了多个函数用来查找元素

- `iterator find(const key_type& __k)` find 函数查找元素为 k 的迭代器位置
- `iterator lower_bound(const key_type& __k)`
    lower\_bound 函数查找小于等于元素 k 的迭代器位置
- `iterator upper_bound(const key_type& __k)`
    upper\_bound 函数查找大于元素 k 的迭代器位置
- `pair<iterator,iterator> equal_range(const key_type& __k)`
    equal\_range 函数返回一个 pair 类型，第一个属性表示大于等于 k 的迭代器位置，第二个是大于 k 的迭代器位置

```c++
void test4() {
    set<int> set1;
    
    for(int i = 0; i < 10; i++) {set1.insert(i+1); }
    
    // 遍历
    for(set<int>::iterator it = set1.begin(); it != set1.end(); it++) {cout << *it <<endl;}
    
    // 查找元素是 5 的迭代器位置
    set<int>::iterator it0 = set1.find(5);
    cout << "it0:" << *it0 <<endl;
    
    // 查找小于等于 5 的元素迭代器位置
    set<int>::iterator it1 = set1.lower_bound(5);
    cout << "it1:" << *it1 <<endl;
    
    // 查找大于 5 的元素迭代器位置
    set<int>::iterator it2 = set1.upper_bound(5);
    cout << "it2:" << *it2 <<endl;
    
    // 返回的 pair 第一个迭代器是 >=5, 另一个是 > 5
    pair<set<int>::iterator, set<int>::iterator> mypair = set1.equal_range(5);
    set<int>::iterator it3 = mypair.first;
    set<int>::iterator it4 = mypair.second;
    cout << "it3:" << *it3 <<endl;
    cout <<"it4:" << *it4 <<endl;
}
```

#### multiset 容器

multiset 容器，与 set 容器相似，但是 multiset 容器中的元素可以重复。另外，他也是自动排序的，容器内部的值不能随便修改，因为有顺序的。

```c++
void test5() {
    // 定义 multiset
    multiset<int> set1;
    
    // 从键盘不停的接收值
    int tmp = 0;
    printf("请输入 multiset 集合的值:");
    scanf("% d", &tmp);
    while(tmp != 0) {set1.insert(tmp);
        scanf("% d", &tmp);
    }
    
    // 迭代器遍历
    for(multiset<int>::iterator it = set1.begin(); it != set1.end(); it++) {cout<< *it <<" ";}
    cout <<endl;
   
    // 删除
    while(!set1.empty()) {multiset<int>::iterator it = set1.begin();
        cout << *it << " ";
        set1.erase(it);
    }
}
```

### STL 中的 map 和 multimap 映射容器

map 和 multimap 是一个键值映射的容器。map 中的键值对都是唯一的，但是 multimap 中一个键可以对应多个值。

- map 和 multimap 是关联式容器，键值成对存在
- map 和 multimap 是红黑变体的平衡二叉树结构
- map 只支持唯一的键值对，集合中的元素是按照一定的顺序排列的
- multimap 中的键可以出现多次
- map 和 multimap 的元素插入过程是按照顺序插入的

#### map 元素的增删改查

map 元素的插入，有两种方式：

1.  调用 insert 函数插入 pair 类型的键值对
2.  直接使用 \[\] 来对键进行复制，类似于 Objective-C 中的 NSMutableDictionary 赋值一样。

map 的 insert 函数返回的是 pair 类型，pair 的第二个参数表示是否插入成功。如果插入的元素键名相同，则插入失败。

map 元素的删除，跟上面其他的容器一样，都是直接调用 erase 函数.

```c++
int main() {
    map<int, string> map1;
    
    //insert 方法插入
    //--1 通过 pair<int, string>(1,”chenhua“) 构造 pair 元素
    map1.insert(pair<int, string>(1,"chenhua"));
    //--2 通过 make_pair 构造 pair 元素
    map1.insert(make_pair(2,"mengna"));
    //--3 通过 value_type 构造 pair 元素
    map1.insert(map<int, string>::value_type(3,"chenmeng"));
    
    //[] 直接插入
    map1[4] = "menghua";
    
    // 重复插入 (插入会不成功)
    pair<map<int, string>::iterator, bool> pair1 = map1.insert(make_pair(2, "haha"));
    if(pair1.second) {cout << "重复插入成功" << endl;} else {cout << "重复插入失败" << endl;}
    
    // 元素的修改
    //map[2] = "22" 的方式，如果不存在键则插入，存在键则修改
    map1[2] = "haha";
    
    // 元素的删除
    //-- 删除值为 "haha" 的元素
    for(map<int, string>::iterator it = map1.begin(); it != map1.end(); it++) {
        if(it->second.compare("haha") == 0) {
            map1.erase(it);
        }
    }
    
    // 遍历
    for(map<int, string>::iterator it = map1.begin(); it != map1.end(); it++) {cout << it->first <<"\t" << it->second <<endl;}
    
    return 0;
}
```

#### map 元素的查找

map 提供了两个函数进行 key 的查找：find 和 equal\_range。

```c++
int main() {
    // 定义 map
    map<int, string> map1;
    map1[1] = "chenhua";
    map1[2] = "mengna";
    
    // 查找 key=100 的键值对
    map<int, string>::iterator it = map1.find(100);
    if(it != map1.end()) {
        cout << "存在 key=100 的键值对";
    } else {
        cout << "不存在" << endl;
    }
    
    
    // 查找 key = 1000 的位置
    // 返回两个迭代器，第一个表示 <=1000 的迭代器位置，第二个是> 1000 的迭代器位置
    pair<map<int, string>::iterator, map<int, string>::iterator> mypair = map1.equal_range(1000);
    if(mypair.first == map1.end()) {
        cout << "大于等于 5 的位置不存在" << endl;
    } else {
        cout << mypair.first->first <<"\t" << mypair.first->second <<endl;
    }
    
    if(mypair.second == map1.end()) {
        cout << "大于 5 的位置不存在" << endl;
    } else {
        cout << mypair.second->first <<"\t" << mypair.second->second <<endl;
    }
    
    return 0;
}
```

#### multimap 容器

multimap 容器，与 map 容器的唯一区别是：multimap 支持多个键值。

由于支持多个键值，multimap 提供了 cout 函数来计算同一个 key 的元素个数。

```c++
class Person {
public:
    string name;    // 姓名
    int age;        // 年龄
    string tel;     // 电话
    double sal;     // 工资
};

void test() {
    Person p1,p2,p3,p4,p5;
    p1.name = "王 1";
    p1.age  = 31;
    
    p2.name = "王 2";
    p2.age  = 31;
    
    p3.name = "张 3";
    p3.age  = 31;
    
    p4.name = "张 4";
    p4.age  = 31;
    
    p5.name = "钱 5";
    p5.age  = 31;
    
    
    multimap<string, Person> map2;
    
    //sale 部门
    map2.insert(make_pair("sale", p1));
    map2.insert(make_pair("sale", p2));
    
    //development 部门
    map2.insert(make_pair("development", p3));
    map2.insert(make_pair("development", p4));
    
    //Finanncial 部门
    map2.insert(make_pair("Finanncial", p5));
    
    
    // 遍历
    for(multimap<string, Person>::iterator it = map2.begin(); it != map2.end(); it++) {cout << it->first <<"\t" << it->second.name <<endl;}
    
    // 按部门显示员工信息
    int developNum = (int) map2.count("development");
    cout << "development 部门人数：" << developNum << endl;
    multimap<string,Person>::iterator it2 = map2.find("development");
    int tag = 0;
    while(it2 != map2.end() && tag < developNum) {
        cout << it2->first <<"\t" << it2->second.name <<endl;
        it2 ++;
        tag ++;
    }
    
    // 把 age=32 修改 name= 32
    for(multimap<string, Person>::iterator it = map2.begin(); it != map2.end(); it++) {if(it->second.age == 32) {
            it->second.name = "32";
        }
    }
}
```

### STL 容器的通用性探究

到这里，STL 的容器我们基本讲解完毕了。STL 的容器主要利用了 C++ 的模板特性来实现。需要注意：

- 容器缓存了节点，节点类要确保支持拷贝 (否则出现浅拷贝问题，导致崩溃)
- 容器中的一般节点类，需要提供拷贝构造函数，并重载等号操作符 (用来赋值)
- 容器在插入元素时，会自动进行元素的拷贝。

针对容器，容器之间也支持拷贝。所以需要注意：

- 除了 queue 和 stack 外，每个容器都提供了可返回迭代器的函数，运用返回的跌打器就可以访问元素
- 通常 STL 不会抛出异常，要求使用者确保传入正确的参数
- 每个容器都提供了一个默认构造函数和一个默认拷贝构造函数

各容器一般来说都有下列函数：默认构造函数、复制构造函数、析构函数、empty()、max_size()、size()、operator=、operator<、operator<=、operator>、operator>=、operator==、operator!=、swap()。

顺序容器和关联容器都共有下列函数：

- begin() ：返回容器第一个元素的迭代器指针；
- end()：返回容器最后一个元素后面一位的迭代器指针；
- rbegin()：返回一个逆向迭代器指针，指向容器最后一个元素；
- rend()：返回一个逆向迭代器指针，指向容器首个元素前面一位；
- clear()：删除容器中的所有的元素；
- erase(it)：删除迭代器指针 it 处元素。

#### STL 容器的元素拷贝

下面，我们演示一下，如果容器元素如果没有实现拷贝构造函数，出现浅拷贝后的崩溃问题。

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Student {
    
public:
    Student(const char *name, int age) {
        cout << "构造函数" << endl;
        
        // 分配内存空间
        m_name = new char [strlen(name) + 1];
        // 值拷贝
        strcpy(m_name, name);
        
        m_age = age;
    }
    
    
    ~Student()
    {
        printf("%p 指向的空间 调用析构函数 \n", m_name);
        if(m_name != NULL) {
            delete [] m_name;
            m_age = 0;
        }
    }
    
private:
    char *m_name;
    int   m_age;
    
};


int main() {
    Student s1 ("chenhua",24);
    
    vector<Student> v1;
    v1.push_back(s1);
    
    return 0;
}
```

上面的代码段，运行后的结果如下：

```
构造函数
0x100302a00 指向的空间 调用析构函数
0x100302a00 指向的空间 调用析构函数
```

运行后，打印出结果后并报错。报错原因是同一个内存空间被释放了 2 次，导致的崩溃。其根本原因是，v1 将 s1 拷贝到容器，由于 Student 没有重写拷贝构造函数，从而出现了浅拷贝，只拷贝了地址。释放的时候毫无疑问出现错误。

如果我们给 Student 重写了拷贝构造函数和重载了等号操作符，则上面的错误就不会出现。

```c++
// 重写拷贝构造函数
Student(const Student &obj) {
    // 分配内存空间
    m_name = new char [strlen(obj.m_name) + 1];
    // 值拷贝
    strcpy(m_name, obj.m_name);
    
    m_age = obj.m_age;
}
    
// 重载等号运算符
Student & operator=(const Student &obj) {
    // 释放旧值
    if(m_name != NULL) {
        delete [] m_name;
        m_age = 0;
    }
    
    // 分配内存空间并赋值
    m_name = new char [strlen(obj.m_name) + 1];
    strcpy(m_name, obj.m_name);
    m_age = obj.m_age;
    
    return *this;
}
```

#### STL 容器的比较

STL 提供了很多容器，每种容器有其自身的特点，我们该如何使用它们呢？

|          |  vector  |   deque  |   list   |   set  | mutliset |     map     |   multimap  |
|:--------:|:--------:|:--------:|:--------:|:------:|:--------:|:-----------:|:-----------:|
| 内存结构 | 单端数组 | 双端数组 | 双向链表 | 二叉树 |  二叉树  |    二叉树   |    二叉树   |
| 随机存取 |    是    |    是    |    否    |   否   |    否    | 对 key 而言是 |      否     |
| 查找速度 |    慢    |    慢    |  非常慢  |   快   |    快    | 对 key 而言快 | 对 key 而言快 |
| 插入删除 |   尾端   | 头尾两端 | 任何位置 |    - |     -  |      -    |      $1     |

#### 各容器的时间复杂度分析

- vector 在头部和中间位置插入和删除的时间复杂度为 O(N)，在尾部插入和删除的时间复杂度为 O(1)，查找的时间复杂度为 O(1)；
- deque 在中间位置插入和删除的时间复杂度为 O(N)，在头部和尾部插入和删除的时间复杂度为 O(1)，查找的时间复杂度为 O(1)；
- list 在任意位置插入和删除的时间复杂度都为 O(1)，查找的时间复杂度为 O(N)；
- set 和 map 都是通过红黑树实现，因此插入、删除和查找操作的时间复杂度都是 O(log N)。
