> @Date    : 2020-09-14 10:34:11
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Linux Shell 实现随机数多种方法（date random uuid）

> 原文：https://www.cnblogs.com/chengmo/archive/2010/10/23/1858879.html 作者：[程默](http://feed.feedsky.com/chengmo) 2010-10-23 10:15

## Table of Contents

- [1、通过时间获得随机数](#1、通过时间获得随机数)
- [2、通过内部系统变量](#2、通过内部系统变量)
- [3、通过系统内部唯一数据生成随机数](#3、通过系统内部唯一数据生成随机数)
- [4、读取 Linux 的 uuid 码](#4、读取-linux-的-uuid-码)
	- [Linux 的 uuid 码](#linux-的-uuid-码)

在日常生活中，随机数实际上经常遇到，想丢骰子，抓阄，还有抽签。呵呵，非常简单就可以实现。那么在做程序设计，真的要通过自己程序设计出随机数那还真的不简单了。现在很多都是操作系统内核会提供相应的 api，这些原始参数是获取一些计算机运行原始信息，如内存，电压，物理信号等等，它的值在一个时间段可以保证是唯一的了。好了，废话我就不说了。呵呵。

shell 脚本程序我们有那些获得随机数方法呢？

## 1、通过时间获得随机数

date

这个也是我们经常用到的，可以说时间是唯一的，也不会重复的，从这个里面获得同一时间的唯一值。适应所有程序里面了。

例子：

```bash
[chengmo@centos5  shell]$ date +%s
#获得时间戳，当前到：1970-01-01 00:00:00 相隔的秒数
#如果用它做随机数，相同一秒的数据是一样的。在做循环处理，多线程里面基本不能满足要求了。
 
[chengmo@centos5  shell]$ date +%N
#获得当前时间的纳秒数据，精确到亿分之一秒。
#这个相当精确了，就算在多cpu，大量循环里面，同一秒里面，也很难出现相同结果，不过不同时间里面还会有大量重复碰撞
 
[chengmo@centos5  shell]$ date +%s%N
#这个可以说比较完美了，加入了时间戳，又加上了纳秒
```

通过上面说明，用它来做随机数的基数了，接下来我们看怎么样获得一段数据内怎么样获得随机数。

```bash
#!/bin/bash

#写个随机函数，调用方法random min max 
#在min 与 max直接获得随机整数
#copyright chengmo QQ:8292669

#获得随机数返回值，shell函数里算出随机数后，更新该值
function random() {
	min=$1;
	max=$2-$1;
	num=$(date +%s+%N);
	((retnum=num%max+min));
	#进行求余数运算即可
	echo $retnum;
	#这里通过echo 打印出来值，然后获得函数的，stdout就可以获得值
	#还有一种返回，定义全价变量，然后函数改下内容，外面读取
}

#得到1-10的seq数据项
for i in {1..10};
do
	out=$(random 2 10000);
	echo $i,"2-10000",$out;
done;
```

**看看运行结果：**

```bash
[chengmo@centos5  shell]$ sh testrandom.sh  
1,2-10000,5600
2,2-10000,5295
3,2-10000,3432
4,2-10000,3148
5,2-10000,9041
6,2-10000,4290
7,2-10000,2380
8,2-10000,9009
9,2-10000,5474
10,2-10000,3664
```

一个循环里面，得到值各不相同。

这个是我们常用方法，适应各种语言，是一个通用算法，就算服务器不提供，某时刻相同唯一数据标记，我们也可以通过这种方法，做自己的伪随机数。下面还有更简单方法呢，不要我们自己做了。

## 2、通过内部系统变量

$RANDOM

其实，Linux 已经提供有个系统环境变量了，直接就是随机数，哈哈，觉得刚学习方法，是不是白费了！！

```bash
[chengmo@centos5  shell]$ echo $RANDOM
[chengmo@centos5  shell]$ echo $RANDOM
 
#连续2次访问，结果不一样，这个数据是一个小于或等于5位的整数
```

可能有疑问了，如果超过 5 位的随机数怎么得到呢？

呵呵，加个固定 10 位整数，然后进行求余，跟例 1 一样了。接下来的例子又是我们自立更生做了。

## 3、通过系统内部唯一数据生成随机数

/dev/random，urandom

我们知道 dev 目录下面，是 Linux 一些默认设备，它给我们感觉就是放的是键盘，硬盘，光驱等设备的对应文件了。 其实 Linux 有些设备很特殊，有特殊用途。前面我们说到的：/[dev/[udp|tcp]/host/port](http://www.cnblogs.com/chengmo/archive/2010/10/22/1858302.html) 比较特殊吧。呵呵，有扯远了。

/dev/random 设备，存储着系统当前运行的环境的实时数据。它可以看作是系统某个时候，唯一值数据，因此可以用作随机数元数据。我们可以通过文件读取方式，读得里面数据。/dev/urandom 这个设备数据与 random 里面一样。只是，它是非阻塞的随机数发生器，读取操作不会产生阻塞。

实例：

```bash
[chengmo@centos5  shell]$ head -1 /dev/urandom
ãÅ†ù…•KTþçanVÕã¹Û&¡õ¾“ô2íùU“ žF¦_ ÿ”†mEðûUráÏ=J¯TŸA•ÌAÚRtÓ

#读一行，怎么是乱码呢？其实它是通过二进制数据保存实时数据的，那么我们怎么样把它变成整型数据呢？

[chengmo@centos5 ~/shell]$ head -200 /dev/urandom | cksum
1615228479 50333
#由于urandom的数据是非常多，不能直接通过cat读取，这里取前200行，其实整个数据都是变化的，取多少也一样是唯一的。
#cksum 将读取文件内容，生成唯一的表示整型数据，只有文件内容不变，生成结果就不会变化,与php crc函数

[chengmo@centos5  shell]$ head -200 /dev/urandom | cksum | cut -f1 -d" "
#cut 以” “分割，然后得到分割的第一个字段数据
```

得到整型数据，然后，类似一的方法就可以获得到随机数了。 题外话：在程序里面，我们经常 md5 得到唯一值，然后是字符串的，如果想表示成整型方式，可以通过 crc 函数. crc 是循环冗余校验，相同数据通过运算，都会得到一串整型数据。现在这种验证应用很广。详细要了解，可以参考：[crc](http://zh.wikipedia.org/zh-cn/%E5%BE%AA%E7%8E%AF%E5%86%97%E4%BD%99%E6%A0%A1%E9%AA%8C).

下面还有个方法，直接从设备读取生成好的 uuid 码。

## 4、读取 Linux 的 uuid 码

在提到这个之前，有个概念，就是什么是 uuid 呢？

UUID 码全称是**通用唯一识别码** (Universally Unique Identifier, UUID), 它 是一个软件建构的标准，亦为**自由软件基金会** (Open Software Foundation, OSF) 的组织在**分布式计算环境** (Distributed Computing Environment, DCE) 领域的一部份。

**UUID 的目的**，是让分布式系统中的所有元素，都能有唯一的辨识信息，而不需要通过中央控制端来做辨识信息的指定。如此一来，每个人都可以创建不与其它人冲突的 UUID。在这样的情况下，就不需考虑数据库创建时的名称重复问题。它会让网络任何一台计算机所生成的 uuid 码，都是互联网整个服务器网络中唯一的。它的原信息会加入硬件，时间，机器当前运行信息等等。

**UUID 格式是：**包含 32 个 [16 进位](http://zh.wikipedia.org/wiki/%E5%8D%81%E5%85%AD%E9%80%B2%E4%BD%8D)数字，以 "-" 连接号分为五段，形式为 8-4-4-4-12 的 32 个字符。范例；550e8400-e29b-41d4-a716-446655440000  , 所以：UUID 理论上的总数为 $ 2^{16 x 8}=2^{128} $，约等于 $ 3.4 x 10^{38} $。也就是说若每奈秒产生 1 兆个 UUID，要花 100 亿年才会将所有 UUID 用完。

其实，大家做数据库设计时候，肯定听说过，guid(**全局唯一标识符**) 码，它其实是与 uuid 类似，由微软支持。 这里编码，基本有操作系统内核产生。大家记得把，在 windows 里面，无论数据库，还是其它软件，很容易得到这个 uuid 编码。

### Linux 的 uuid 码

Linux 的 uuid 码也是有内核提供的，在 /proc/sys/kernel/random/uuid 这个文件内。其实，random 目录，里面还有很多其它文件，都与生成 uuid 有关系的。

```bash
[chengmo@centos5 ~/shell]$ cat /proc/sys/kernel/random/uuid
dff68213-b700-4947-87b1-d9e640334196
[chengmo@centos5 ~/shell]$ cat /proc/sys/kernel/random/uuid
7b57209a-d285-4fd0-88b4-9d3162d2e1bc
#连续2次读取，得到的uuid是不同的
 
[chengmo@centos5 ~/shell]$ cat /proc/sys/kernel/random/uuid| cksum | cut -f1 -d" "
#同上方法得到随机整数
```

这是 Linux 下面，几种常见活动随机数整数方法，除了第一个是不同外，其实后 3 个，产生随机码的伪数据来源，都与 /dev/random 设备有关系。只是它们各自呈现不同而已。如果你还有更多其它方法，请给我消息，与大家分享了。