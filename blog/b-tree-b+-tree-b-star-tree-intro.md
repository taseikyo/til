> @Date    : 2020-07-29 22:18:06
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo


> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/27700617)

# 平衡二叉树、B树、B+树、B* 树 理解其中一种你就都明白了

**1、平衡二叉树**
-----------

*   **概念**

平衡二叉树是基于二分法的策略提高数据的查找速度的二叉树的数据结构；

*   **特点：**

平衡二叉树是采用二分法思维把数据按规则组装成一个树形结构的数据，用这个树形结构的数据减少无关数据的检索，大大的提升了数据检索的速度；平衡二叉树的数据结构组装过程有以下规则：

（1）非叶子节点只能允许最多两个子节点存在。

（2）每一个非叶子节点数据分布规则为左边的子节点小当前节点的值，右边的子节点大于当前节点的值 (这里值是基于自己的算法规则而定的，比如 hash 值)；

![](../images/v2-28e39093993f673de576f57ea614d604_r.jpg)

平衡树的层级结构：因为平衡二叉树查询性能和树的层级（h 高度）成反比，h 值越小查询越快、为了保证树的结构左右两端数据大致平衡降低二叉树的查询难度一般会采用一种算法机制实现节点数据结构的平衡，实现了这种算法的有比如 [Treap](https://link.zhihu.com/?target=http%3A//baike.baidu.com/item/Treap)、红黑树，使用平衡二叉树能保证数据的左右两边的节点层级相差不会大于 1.，通过这样避免树形结构由于删除增加变成线性链表影响查询效率，保证数据平衡的情况下查找数据的速度近于二分法查找；

![](../images/v2-2b52d4e523f374f41b5429cd587443db_r.jpg)

总结平衡二叉树特点：

（1）非叶子节点最多拥有两个子节点；

（2）非叶子节值大于左边子节点、小于右边子节点；

（3）树的左右两边的层级数相差不会大于 1;

（4）没有值相等重复的节点;

**2、B 树 (B-tree)**
------------------

注意: 之前有看到有很多文章把 B 树和 B-tree 理解成了两种不同类别的树，其实这两个是同一种树;

*   **概念：**

B 树和平衡二叉树稍有不同的是 B 树属于多叉树又名平衡多路查找树（查找路径不只两个），数据库索引技术里大量使用者 B 树和 B + 树的数据结构，让我们来看看他有什么特点;

*   **规则：**

（1）排序方式：所有节点关键字是按递增次序排列，并遵循左小右大原则；

（2）子节点数：非叶节点的子节点数 > 1，且 <=M ，且 M>=2，空树除外（注：M 阶代表一个树节点最多有多少个查找路径，M=M 路, 当 M=2 则是 2 叉树, M=3 则是 3 叉）；

（3）关键字数：枝节点的关键字数量大于等于 ceil(m/2)-1 个且小于等于 M-1 个（注：ceil() 是个朝正无穷方向取整的函数 如 ceil(1.1) 结果为 2);

（4）所有叶子节点均在同一层、叶子节点除了包含了关键字和关键字记录的指针外也有指向其子节点的指针只不过其指针地址都为 null 对应下图最后一层节点的空格子;

最后我们用一个图和一个实际的例子来理解 B 树（这里为了理解方便我就直接用实际字母的大小来排列 C>B>A）

![](../images/v2-2c2264cc1c6c603dfeca4f84a2575901_r.jpg)

*   **B 树的查询流程：**

如上图我要从上图中找到 E 字母，查找流程如下

（1）获取根节点的关键字进行比较，当前根节点关键字为 M，E<M（26 个字母顺序），所以往找到指向左边的子节点（二分法规则，左小右大，左边放小于当前节点值的子节点、右边放大于当前节点值的子节点）；

（2）拿到关键字 D 和 G，D<E<G 所以直接找到 D 和 G 中间的节点；

（3）拿到 E 和 F，因为 E=E 所以直接返回关键字和指针信息（如果树结构里面没有包含所要查找的节点则返回 null）；

*   **B 树的插入节点流程**

定义一个 5 阶树（平衡 5 路查找树;），现在我们要把 3、8、31、11、23、29、50、28 这些数字构建出一个 5 阶树出来;

遵循规则：

（1）节点拆分规则：当前是要组成一个 5 路查找树，那么此时 m=5, 关键字数必须 <=5-1（这里关键字数> 4 就要进行节点拆分）；

（2）排序规则：满足节点本身比左边节点大，比右边节点小的排序规则;

先插入 3、8、31、11

![](../images/v2-e1d65c9c6236d4768c89e8e103e12583_r.jpg)

再插入 23、29

[](../images/v2-66cdb6187cbc5227fd8c4aabe7282e6c_r.jpg)

再插入 50、28

[](../images/v2-3057eaab2b1764dd51c2a8658791cc98_r.jpg)

*   **B 树节点的删除**

**规则：**

（1）节点合并规则：当前是要组成一个 5 路查找树，那么此时 m=5, 关键字数必须大于等于 ceil（5/2）（这里关键字数 < 2 就要进行节点合并）；

（2）满足节点本身比左边节点大，比右边节点小的排序规则;

（3）关键字数小于二时先从子节点取，子节点没有符合条件时就向向父节点取，取中间值往父节点放；

![](../images/v2-a0f981fc847772cb28869927cd4fe66d_r.jpg)

**特点：**

B 树相对于平衡二叉树的不同是，每个节点包含的关键字增多了，特别是在 B 树应用到数据库中的时候，数据库充分利用了磁盘块的原理（磁盘数据存储是采用块的形式存储的，每个块的大小为 4K，每次 IO 进行数据读取时，同一个磁盘块的数据可以一次性读取出来）把节点大小限制和充分使用在磁盘快大小范围；把树的节点关键字增多后树的层级比原来的二叉树少了，减少数据查找的次数和复杂度;

**3、B + 树**
-----------

*   **概念**

B + 树是 B 树的一个升级版，相对于 B 树来说 B + 树更充分的利用了节点的空间，让查询速度更加稳定，其速度完全接近于二分法查找。为什么说 B + 树查找的效率要比 B 树更高、更稳定；我们先看看两者的区别

*   **规则**

（1）B + 跟 B 树不同 B + 树的**非叶子**节点不保存关键字记录的指针，只进行数据索引，这样使得 B + 树每个**非叶子**节点所能保存的关键字大大增加；

（2）B + 树**叶子**节点保存了父节点的所有关键字记录的指针，所有数据地址必须要到叶子节点才能获取到。所以每次数据查询的次数都一样；

（3）B + 树叶子节点的关键字从小到大有序排列，左边结尾数据都会保存右边节点开始数据的指针。

（4）非叶子节点的子节点数 = 关键字数（来源百度百科）（根据各种资料 这里有两种算法的实现方式，另一种为非叶节点的关键字数 = 子节点数 - 1（来源维基百科)，虽然他们数据排列结构不一样，但其原理还是一样的 Mysql 的 B + 树是用第一种方式实现）;

![](../images/v2-5f069fd820637db1b877fdd6799a2b67_r.jpg)

**（百度百科算法结构示意图）**

![](../images/v2-9644d1a1f83d3e45da779f2e63c35d55_r.jpg)

**（维基百科算法结构示意图）**

*   **特点**

1、B+ **树的层级更少**：相较于 B 树 B + 每个**非叶子**节点存储的关键字数更多，树的层级更少所以查询数据更快；

2、B+ **树查询速度更稳定**：B + 所有关键字数据地址都存在**叶子**节点上，所以每次查找的次数都相同所以查询速度要比 B 树更稳定;

3、B+ **树天然具备排序功能：**B + 树所有的**叶子**节点数据构成了一个有序链表，在查询大小区间的数据时候更方便，数据紧密性很高，缓存的命中率也会比 B 树高。

4、B+ **树全节点遍历更快：**B + 树遍历整棵树只需要遍历所有的**叶子**节点即可，，而不需要像 B 树一样需要对每一层进行遍历，这有利于数据库做全表扫描。

**B 树**相对于 **B + 树**的优点是，如果经常访问的数据离根节点很近，而 **B 树**的**非叶子**节点本身存有关键字其数据的地址，所以这种数据检索的时候会要比 **B + 树**快。

**4、B * 树**
-----------

*   **规则**

B * 树是 B + 树的变种，相对于 B + 树他们的不同之处如下：

（1）首先是关键字个数限制问题，B + 树初始化的关键字初始化个数是 cei(m/2)，b * 树的初始化个数为（cei(2/3*m)）

（2）B + 树节点满时就会分裂，而 B * 树节点满时会检查兄弟节点是否满（因为每个节点都有指向兄弟的指针），如果兄弟节点未满则向兄弟节点转移关键字，如果兄弟节点已满，则从当前节点和兄弟节点各拿出 1/3 的数据创建一个新的节点出来；

*   **特点**

在 B + 树的基础上因其初始化的容量变大，使得节点空间使用率更高，而又存有兄弟节点的指针，可以向兄弟节点转移关键字的特性使得 B * 树额分解次数变得更少；

![](../images/v2-e8bf8ee3230f3d39d59ce5e76a2ee32e_r.jpg)

**5、 总结**
---------

**1、相同思想和策略**

从平衡二叉树、B 树、B + 树、B * 树总体来看它们的贯彻的思想是相同的，都是采用二分法和数据平衡策略来提升查找数据的速度；

**2、不同的方式的磁盘空间利用**

不同点是他们一个一个在演变的过程中通过 IO 从磁盘读取数据的原理进行一步步的演变，每一次演变都是为了让节点的空间更合理的运用起来，从而使树的层级减少达到快速查找数据的目的；

如果还没理解的话推荐以下资料描叙的很详细：

补充概念：

附（二分法查找）：[二分法查找原理 - 知乎专栏](https://zhuanlan.zhihu.com/p/27597160)

附（B、B+、B * 树）：[从 B 树、B + 树、B * 树谈到 R 树](https://link.zhihu.com/?target=http%3A//blog.csdn.net/v_JULY_v/article/details/6530142/)

附（B、B+、B * 树）：[end&#x27;s coding life](https://link.zhihu.com/?target=http%3A//blog.csdn.net/endlu/article/details/51720299)

附：[B 树和 B + 树的插入、删除图文详解 - nullzx - 博客园](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/nullzx/p/8729425.html)