> @Date    : 2020-09-25 10:42:54
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# CSAPP：深入理解计算机系统（3rd）

- https://book.douban.com/subject/26912767/

和第 2 版相比，本版内容上大的变化是，从以 IA32 和 x86-64 为基础转变为完全以 x86-64 为基础要更新如下：

- 基于 x86-64，大量地重写代码，首次介绍对处理浮点数据的程序的机器级支持
- 处理器体系结构修改为支持 64 位字和操作的设计
- 引入更多的功能单元和更复杂的控制逻辑，使基于程序数据流表示的程序性能模型预测更加可靠
- 扩充关于用 GOT 和 PLT 创建与位置无关代码的讨论，描述了更加强大的链接技术（比如库打桩）
- 增加了对信号处理程序更细致的描述，包括异步信号安全的函数等
- 采用新函数，更新了与协议无关和线程安全的网络编程

感谢蛤蛤的工作让我少了自行 OCR 的工作量：https://hansimov.gitbook.io/csapp/

## Table of Contents

- Part II 在系统上运行程序
	- [7.链接](src/07.linking.md)
	- [8.异常控制流](src/08.exceptional-control-flow.md)
	- [9.虚拟内存](src/09.virtual-memory.md)
- Part III 程序间的交流和通信
	- [10.系统级 IO](src/10.system-level-io.md)
