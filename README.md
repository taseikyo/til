<p align="center">
	<a href="#readme"><img src="images/til-everydaycat.jpg" alt="Today I Learned" title="Today I Learned"></a>
</p>

建议本地配合 Markdown Preview Plus 扩展观看，由于有的地方使用了 latex 公式，直接在 GitHub 上看显示不了。

加文件头（`@Date` `@Author`）是因为我喜欢给东西打上时间的 tag，有时间 tag 的东西后面回头看会很有沉淀感，我很喜欢这种感觉。从某个时间点之后我都是用 [简读](https://simpread.pro/) 直接转的 md，然后会手动加上作者与发布时间。

### Reference

- [ascii codes](http://www.cplusplus.com/doc/ascii/)
- [c++ reference](http://www.cplusplus.com/reference/)
- [c++ containers library](http://www.cplusplus.com/reference/stl/)
- [PEP 8 -- Style Guide for Python Code](https://www.python.org/dev/peps/pep-0008/)
- [nayuki / Project-Euler-solutions](https://github.com/nayuki/Project-Euler-solutions)
- [labuladong的算法小抄](https://labuladong.gitbook.io/algo/)
- [CyC2018/CS-Notes：技术面试必备基础知识](https://github.com/CyC2018/CS-Notes)
- [huihut/interview：C/C++ 技术面试基础知识总结](https://github.com/huihut/interview)

### Code

- [算法题常用技巧 - taseikyo 总结版](code/tricks-to-algo-problems-taseikyo.md)
- [leetcode](code/leetcode)
- [coding-interviews](code/coding-interviews)
- [cracking-the-coding-interview](code/cracking-the-coding-interview)
- [每日一道有趣的编程题](code/daily-problem)

### DIY-Algos

- [动手实现一个 string 类（C++）](cpp/diy-algos/string)
- [动手实现一个 shared_ptr 类](cpp/diy-algos/shared_ptr)，遇到了模板类的声明与定义分开放置编译的问题（见下面）

### C++

- [如何遍历 vector](cpp/how-to-iterate-vector.md)
- [vector 与 char* 相互转换](cpp/conversion-between-vector-and-char-star.md)
- [C++ STL 简介](cpp/cpp-slt-intro.md)
- [关于 sizeof 的一些思考](cpp/some-thoughts-on-sizeof.md)
- [虚函数简介](cpp/vtable-intro.md)
- [C++ 设计模式简介](cpp/cpp-design-pattern-intro.md)
- [引用折叠和完美转发](cpp/reference-collapsing-and-perfect-forward-intro.md)
- [奇妙的 enum class，enum struct 组合](cpp/enum-class-intro.md)
- [C++11 继承构造函数](cpp/c11-inheriting-constructors-intro.md)
- [子类如何调用父类重载的运算符](cpp/subclass-calls-the-operator-overloaded-by-the-parent-class.md)
- [五种排序算法的 C++ 实现以及时间分析](cpp/comparison-of-sorting-algos)
- [模板的全特化与偏特化](cpp/full-specialization-and-partial-specialization-of-templates.md)
- [shared_ptr 传参和复制的引用计数问题](cpp/shared_ptr-reference-counting-problem-of-parameter-passing-and-copying.md)
- [new object() 和 new object 区别][cpp-200901]
- [模板类的声明与定义分开放置编译的问题](cpp/why-can't-i-separate-the-definition-of-my-templates-class-from-its-declaration-and-put-it-inside-a-cpp-file.md)
- [解决模板类的编译问题](cpp/how-can-i-avoid-linker-errors-with-my-template-functions.md)

### Python

- [从 7z 压缩包中读取文件](python/read-files-from-7z.md)
- [doctest 测试模块使用简介](python/doctest-intro.md)
- [Python 实用技巧](python/useful-python-tricks.md)

### Blog

- [二叉树的莫里斯遍历 / Morris Traversal](blog/tree-morris-traversal.md)
- [尾调用优化 / Tail Call Optimization](blog/tail-call-optimization.md)
- [TCP 与 UDP 的区别](blog/tcp-vs-udp.md)
- [Redis 简介 - CyC2018 / CS-Notes](blog/redis-cyc2018.md)
- [存储系统中的各种写放大 / Write Amplification](blog/storage-system-write-amplification.md)
- [跳表简介 / Skip List](blog/skip-list-intro.md)
- [红黑树简介 / Red-Black Tree](blog/red-black-tree-intro.md)
- [如何阅读复杂的 C 类型声明 / How To Read C Declarations / Clockwise/Spiral Rule](blog/how-to-read-c-declarations-spiral-rule-anderson.md)
- [数据库原理简介 - CyC2018 / CS-Notes](blog/database-system-principle-intro-cyc2018.md)
- [如何在 main 函数之前执行其它函数](blog/how-to-run-other-functions-before-main-is-executed.md)
- [STL 内存池简介](blog/stl-memory-pool-intro.md)
- [select、poll、epoll 之间的区别](blog/the-difference-between-select-poll-epoll.md)
- [微信红包算法以及带上下限的红包算法](blog/wechat-red-envelope-algorithm-and-red-envelope-algorithm-with-upper-and-lower-limits.md)
- [C++ 中的虚函数 (表) 实现机制以及用 C 语言对其进行的模拟实现](blog/the-implementation-mechanism-of-virtual-function-table-in-c++-and-its-implementation-in-c.md)
- [平衡二叉树、B 树、B+ 树、B* 树理解其中一种你就都明白了](blog/b-tree-b+-tree-b-star-tree-intro.md)
- [哈夫曼树（赫夫曼树、最优树）及C语言实现](blog/huffman-tree-intro.md)
- [一文详解 TCP/IP 协议栈](blog/tcp-ip-protocol-stack-intro.md)
- [数据库 SQL 调优的几种方式](blog/several-ways-of-sql-tuning.md)
- [C++ 后端开发面经整理 - 牛客网](blog/cpp-back-end-developer-interview-experience-record.md)
- [几种洗牌与抽样算法](blog/shuffle-and-sampling-algos.md)
- [所有 blog 文章>>](blog.md)

### Book

- [Python One-Liners](book/python-one-liners) ❌❌
- [C++ Primer, 5th Edition](book/cpp-primer-5nd-edition) 👍👍
- [Effective Python, 2nd Edition](book/effective-python-2nd-edition)  👍👍
- [算法竞赛入门经典](book/算法竞赛入门经典) 👍👍
- [程序员的自我修养](book/程序员的自我修养) 👍👍
- [Tiny Python Projects](book/tiny-python-projects)
- [Linux System Programming, 2nd Edition](book/linux-system-programming-2nd-edition)
- [剑指 Offer](book/剑指Offer)

### Course

- [七月算法](course/july-algorithm)
- [数据结构 - 郝斌](course/haobin-data-structure)
- [MIT 18.06 Linear Algebra, Spring 2005](course/mit-18.06-linear-algebra-spring-2005)

### License

Copyright (c) 2020 Lewis Tian. Licensed under the MIT license.

[cpp-200901]:cpp/the-difference-between-new-object()-and-new-object.md