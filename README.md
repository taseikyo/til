<p align="center">
	<a href="#readme"><img src="images/2020/09/til-everydaycat.jpg" alt="Today I Learned" title="Today I Learned"></a>
</p>

建议本地配合 Markdown Preview Plus 扩展观看，由于有的地方使用了 latex 公式，直接在 GitHub 上看显示不了。

加文件头（`@Date` `@Author`）是因为我喜欢给东西打上时间的 tag，有时间 tag 的东西后面回头看会很有沉淀感，我很喜欢这种感觉。从某个时间点之后我都是用 [简读](https://simpread.pro/) 直接转的 md，然后会手动加上作者与发布时间。

如何搜索？参考 [ruanyf/weekly](https://github.com/ruanyf/weekly) 给出的方法：

1. 使用 [Sourcegraph.com](https://sourcegraph.com/github.com/taseikyo/til) 进行搜索
2. 使用 GitHub 自带的搜索，但只支持搜索英文单词
3. 将这个仓库克隆到本地，然后在仓库目录使用下面的命令

```Bash
grep -nri [搜索词] [目录]
# 下面将显示每条记录的序号，但是会没有颜色
grep -nri [搜索词] [目录]| cat --number
```

比如搜索 *博客* 中含有 **内核源码** 关键词的博客：

```Bash
til [master●] % grep -nri "内核源码" blog
blog/linux-physical-memory-description.md:13:本文以 linux-2.6.32-220.el6 版本内核源码为基础，介绍 Linux 内核中有关物理内存的概念，和如何描述物理内存。注意：本文中涉及到的仅是和物理内存有关的概念、数据结构。和地址如何映射、线性地址、物理地址；内存如何分配 / 回收等概念无关。
blog/use-the-exception-table-to-handle-page-faults-in-linux-kernel-mode.md:126:那么，这个所谓的修复地址又是如何生成的呢？是系统自动生成的吗？答案当然是否定的，这些修复指令都是编程人员通过 as 提供的扩 展功能写进内核源码中的。下面我们就来分析一下其实现机制。
blog/use-the-exception-table-to-handle-page-faults-in-linux-kernel-mode.md:323:也许有的读者会问了，既然不执行，前面的例子和围绕例子所展开的讨论又有什么作用呢？大家大可打消这样的疑虑，我们前面的分析并 没有白费，因为真正的内核异常表中地址对的生成机制和前面讲述的原理是完全一样的，笔者通过一个运行在用户空间的程序来讲解也是希望让读者能够更加容易的理解异常表的机制，不至于陷入到内核源码的汪洋大海中去。现在，我们可以自己通过 objdump 工具查看一下内核中的异常表：
```

比如搜索 *书* 中含有 **参数绑定** 关键词的章节：

```Bash
til [master●] % grep -nri "参数绑定" book
book/cpp-primer-5nd-edition/src/10.generic-algorithms.md:306:### 参数绑定
book/cpp-primer-5nd-edition/src/10.generic-algorithms.md:365:此 bind 调用生成一个可调用对象，将 checksize 的第二个参数绑定到 sz 的值。当 find_if 对 words 中的 string 调用这个对象时，这些对象会调用 check_size，将给定的 string 和 sz 传递给它。因此，find_if 可以有效地对输入序列中每个 string 调用 check_size，实现 string 的大小与 sz 的比较。
book/cpp-primer-5nd-edition/src/10.generic-algorithms.md:461:### 向后兼容：参数绑定
book/fluent-python/src/05.first-class-functions.md:489:inspect.Signature 对象有个 bind 方法，它可以把任意个参数绑定到签名中的形参
```

## Table of Contents

- [Reference：有用链接](#reference)
- [Code：刷题的代码](#code)
- [DIY-Algos：自己实现的辣鸡类](#diy-algos)
- [C++：关于 C艹 的一些技巧或者文章](#c)
- [Python：关于 Python 的一些技巧或者文章](#python)
- [Blog：有趣有技术的技术博客](#blog)
- [Book：看过的书的记录](#book)
- [Course：看过的公开课或者技术课的记录](#course)

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

- [如何遍历 vector](cpp/2020/06/how-to-iterate-vector.md)
- [vector 与 char* 相互转换](cpp/2020/06/conversion-between-vector-and-char-star.md)
- [C++ STL 简介](cpp/2020/06/cpp-slt-intro.md)
- [关于 sizeof 的一些思考](cpp/2020/07/some-thoughts-on-sizeof.md)
- [虚函数简介](cpp/2020/07/vtable-intro.md)
- [C++ 设计模式简介](cpp/2020/07/cpp-design-pattern-intro.md)
- [引用折叠和完美转发](cpp/2020/07/reference-collapsing-and-perfect-forward-intro.md)
- [奇妙的 enum class，enum struct 组合](cpp/2020/07/enum-class-intro.md)
- [C++11 继承构造函数](cpp/2020/07/c11-inheriting-constructors-intro.md)
- [子类如何调用父类重载的运算符](cpp/2020/08/subclass-calls-the-operator-overloaded-by-the-parent-class.md)
- [五种排序算法的 C++ 实现以及时间分析](cpp/comparison-of-sorting-algos)
- [模板的全特化与偏特化](cpp/2020/08/full-specialization-and-partial-specialization-of-templates.md)
- [shared_ptr 传参和复制的引用计数问题](cpp/2020/08/shared_ptr-reference-counting-problem-of-parameter-passing-and-copying.md)
- [new object() 和 new object 区别][cpp-200901]
- [模板类的声明与定义分开放置编译的问题](cpp/2020/09/why-can't-i-separate-the-definition-of-my-templates-class-from-its-declaration-and-put-it-inside-a-cpp-file.md)
- [解决模板类的编译问题](cpp/2020/09/how-can-i-avoid-linker-errors-with-my-template-functions.md)
- [C++17 新特性个人总结](cpp/2020/09/c17-new-features-intro.md)

### Python

- [从 7z 压缩包中读取文件](python/2020/07/read-files-from-7z.md)
- [doctest 测试模块使用简介](python/2020/08/doctest-intro.md)
- [Python 实用技巧](python/2020/09/useful-python-tricks.md)

### Blog

- [二叉树的莫里斯遍历 / Morris Traversal](blog/2020/06/tree-morris-traversal.md)
- [尾调用优化 / Tail Call Optimization](blog/2020/06/tail-call-optimization.md)
- [TCP 与 UDP 的区别](blog/2020/06/tcp-vs-udp.md)
- [Redis 简介 - CyC2018 / CS-Notes](blog/2020/06/redis-cyc2018.md)
- [存储系统中的各种写放大 / Write Amplification](blog/2020/06/storage-system-write-amplification.md)
- [跳表简介 / Skip List](blog/2020/06/skip-list-intro.md)
- [红黑树简介 / Red-Black Tree](blog/2020/06/red-black-tree-intro.md)
- [如何阅读复杂的 C 类型声明 / How To Read C Declarations / Clockwise/Spiral Rule](blog/2020/06/how-to-read-c-declarations-spiral-rule-anderson.md)
- [数据库原理简介 - CyC2018 / CS-Notes](blog/2020/06/database-system-principle-intro-cyc2018.md)
- [如何在 main 函数之前执行其它函数](blog/2020/07/how-to-run-other-functions-before-main-is-executed.md)
- [STL 内存池简介](blog/2020/07/stl-memory-pool-intro.md)
- [select、poll、epoll 之间的区别](blog/2020/07/the-difference-between-select-poll-epoll.md)
- [微信红包算法以及带上下限的红包算法](blog/2020/07/wechat-red-envelope-algorithm-and-red-envelope-algorithm-with-upper-and-lower-limits.md)
- [C++ 中的虚函数 (表) 实现机制以及用 C 语言对其进行的模拟实现](blog/2020/07/the-implementation-mechanism-of-virtual-function-table-in-c++-and-its-implementation-in-c.md)
- [平衡二叉树、B 树、B+ 树、B* 树理解其中一种你就都明白了](blog/2020/07/b-tree-b+-tree-b-star-tree-intro.md)
- [哈夫曼树（赫夫曼树、最优树）及C语言实现](blog/2020/11/huffman-tree-intro.md)
- [一文详解 TCP/IP 协议栈](blog/2020/08/tcp-ip-protocol-stack-intro.md)
- [数据库 SQL 调优的几种方式](blog/2020/08/several-ways-of-sql-tuning.md)
- [C++ 后端开发面经整理 - 牛客网](blog/2020/08/cpp-back-end-developer-interview-experience-record.md)
- [几种洗牌与抽样算法](blog/2020/08/shuffle-and-sampling-algos.md)
- [所有 blog 文章>>](blog/)

### Book

- [x] [Python One-Liners](book/python-one-liners) ❌❌
- [C++ Primer, 5th Edition](book/cpp-primer-5nd-edition) 👍👍
- [Effective Python, 2nd Edition](book/effective-python-2nd-edition)  👍👍
- [算法竞赛入门经典](book/算法竞赛入门经典) 👍
- [程序员的自我修养](book/程序员的自我修养) 👍👍
- [Tiny Python Projects](book/tiny-python-projects)
- [Linux System Programming, 2nd Edition](book/linux-system-programming-2nd-edition)
- [x] [剑指 Offer](book/剑指Offer)
- [C++17 - The Complete Guide](book/cpp17-the-complete-guide) 👍
- [Fluent Python（流畅的 Python）](book/fluent-python) 👍
- [CSAPP: Computer Systems: A Programmer's Perspective, 3rd Edition](book/computer-systems-a-programmers-perspective-3rd-edition) 👍👍

### Course

- [七月算法](course/july-algorithm)
- [数据结构 - 郝斌](course/haobin-data-structure)
- [MIT 18.06 Linear Algebra, Spring 2005](course/mit-18.06-linear-algebra-spring-2005)

### 秋招详情

<details>
<summary>^_^</summary>

当初建这个库就是为了应付今年的秋招，也就是说从六月份才开始准备，所以其实很匆忙，很多知识点没复习到，也没投几家公司，下面是最后的结果：

- 被动挂
	- 阿里，笔试或者性格测试挂，笔试 0 ac，性格测试太弱智我乱选的
	- 猿辅导，笔试挂，收获第一封也是唯一一封感谢信
	- 微信，2+2+1，两轮技术面，两轮面委会，一轮 HR，明明都云证了，最后审批挂，不是很懂
	- 美团，投晚了，笔试完就没消息了，后面 11 月份面试官发短信约面试，我：？
- 主动拒
	- 小米，拒了好几次笔试
	- 农行，拒了面试
- 意向书
	- bilibili，4，没有 hr 面，挺怪的，最后开了劝退价，笑了
	- pdd，2+1，两轮技术面体验不错，听说工作强度太大，放弃了
	- 快手，3+1，base 北京，想长远发展还是退却了
	- 字节（抖音），3，也是没有 hr 面，一天 3 轮技术面，体验还不错
</details>

### License

Copyright (c) 2020 Lewis Tian. Licensed under the MIT license.

[cpp-200901]:cpp/the-difference-between-new-object()-and-new-object.md