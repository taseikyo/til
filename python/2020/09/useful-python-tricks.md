> @Date    : 2020-09-02 19:39:27
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Python 实用技巧

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/98731459) [kashimoto](https://www.zhihu.com/people/li-yu-xiang-21-20)

## Table of Contents

- [常用技巧](#常用技巧)
- [基本类型](#基本类型)
	- [对整数](#对整数)
	- [对浮点数](#对浮点数)
	- [对二进制](#对二进制)
	- [字符串](#字符串)
	- [统计奇偶个数](#统计奇偶个数)
- [queue (heapq)](#queue-(heapq))
	- [基本操作](#基本操作)
	- [top k freq element](#top-k-freq-element)
- [Deque](#deque)
- [List](#list)
	- [展开 list](#展开-list)
	- [range 中第二个元素比第一个元素小](#range-中第二个元素比第一个元素小)
	- [判断一个列表为空得最佳实践](#判断一个列表为空得最佳实践)
	- [如何合并两个列表](#如何合并两个列表)
	- [Python 中如何复制一个列表](#python-中如何复制一个列表)
	- [如何利用下标从列表中删除一个元素](#如何利用下标从列表中删除一个元素)
	- [如何获取 list 中包含某个元素所在的下标](#如何获取-list-中包含某个元素所在的下标)
	- [如何扁平一个二维数组](#如何扁平一个二维数组)
	- [如何将一个列表切分成若干个长度相同的子序列](#如何将一个列表切分成若干个长度相同的子序列)
	- [按照元素对 list 进行 split](#按照元素对-list-进行-split)
- [Collections](#collections)
	- [Counter](#counter)
- [Itertools](#itertools)
	- [itertools.groupby【把相邻的压缩】](#itertools.groupby【把相邻的压缩】)
    - [itertools.permutations and combinations](#itertools.permutations-and-combinations)
    - [itertools.product](#itertools.product)
- [Set](#set)
	- [多 Set 批量操作](#多-set-批量操作)
- [Sort](#sort)
	- [按照类的成员排序](#按照类的成员排序)
	- [字典按照键值排序](#字典按照键值排序)
	- [python comparetor](#python-comparetor)
- [Other](#other)
	- [列表解析 和 map 的性能](#列表解析-和-map-的性能)
- [Python 2.7 里 [...] 是什么？](#python-2.7-里-[...]-是什么？)
- [动态条件](#动态条件)
- [链式调用](#链式调用)

## 常用技巧

* 如何优雅地 copy 一个 list? arr[:]
* 如何遍历字典？dict.items()
* 如何将任何事物转换成迭代器？iter(pp2fr.keys()))
* 如何定义最大值？import sys; sys.maxsize
* 在判断两个浮点数 a 和 b 是否相等时, 不要用 a==b, 应该判断二者之差的绝对值 `abs(f1 - f2) <= allowed_error`。
* 使用 reserve 来避免不必要的重新分配
* 如果序列中存在的元素数量少于你要的，例如，你请求 a[:-2] 但是 a 只有一个元素，你会得到一个空列表，而不是一个错误. 有时候你或许希望返回的是一个错误，所以你必须知道这点
* XOR is its own inverse to find the missing element in linear time.
* ordered dictionary 的所有操作都是常数时间
* bool 的更新 changed |= check(i)
* random `import random; print(random.random())`
* 判断浮点数整数 num % 1 ==1
* dict.pop(k,d) 其中 d 是 k 找不到时的默认值
* 判断两个数的符号 sig = (a < 0) == (b < 0)
* 直观的不等式 print(1> 1 > 0)
* sum(i == j for i, j in zip(secret, guess)) 判断有多少符合条件
* 看到除法就想到对 0 的特殊处理
* 随机抽取变量 `random.choice(arr)`
* 判断二维矩阵的有效性 `if not any(board): return`
* 生成交换序列 `itertools.combinations(range(W), 2)`
* 多使用 dict.get()，这样找不到的话返回 None 而不是报错
* 在搜索问题中，优雅地遍历当前节点的邻居`for i in range(x-1, x+2) for j in range(y-1,y+2)`
* 如何设置 max 函数的默认值（这点在 arr 为空的时候特别有用）？max_num = max(arr, default=0)

## 基本类型

### 对整数

```Python
round(x[, n])
math.floor(x)
math.ceil(x)
```

### 对浮点数

```Python
(-2.0).is_integer()
```

### 对二进制

* python convert into 32 bin '{:032b}'
* 获取最大位数： t.bit_length()

```Python
>>> n = -37
>>> bin(n)
'-0b100101'
>>> n.bit_length()
```

### 字符串

```Python
str.index(sub[, start[, end]])¶
str.isalnum()
str.isalpha()
str.isdigit()
str.isupper()
str.islower()
str.isspace()
str.endswith(suffix[, start[, end]])
str.center(width[, fillchar])
str.count(sub[, start[, end]])
str.ljust(width[, fillchar])
str.lstrip([chars])
str.rfind(sub[, start[, end]])
str.rindex(sub[, start[, end]])
str.rjust(width[, fillchar])
str.lower()
str.upper()
str.partition(sep)
str.rpartition(sep)
str.swapcase()
# Split the string at the first occurrence of sep, and return a 3-tuple containing the part before the separator, the separator itself, and the part after the separator. If the separator is not found, return a 3-tuple containing the string itself, followed by two empty strings.
>>> '   spacious   '.lstrip()
'spacious   '
>>> 'www.example.com'.lstrip('cmowz.')
'example.com'
```

### 统计奇偶个数

```Python
chips=[n%2 for n in chips]
n1,n2=chips.count(0),chips.count(1)
return min(n1,n2)
```

## queue (heapq)

### 基本操作

```Python
import heapq

q = []

for i in range(5):
    heapq.heapq_push

while not q.empty():
    print q.get()
```

### top k freq element

```Python
heapq.nlargest(k, count.keys(), key=count.get)
```

## Deque

```Python
from collections import deque
d = deque('ghi')                 # make a new deque with three items
d.append('j')                    # add a new entry to the right side
d.appendleft('f')                # add a new entry to the left side
# deque(['f', 'g', 'h', 'i', 'j'])

d.pop()                          # return and remove the rightmost item
# 'j'
d.popleft()                      # return and remove the leftmost item
# 'f'
list(d)                          # list the contents of the deque
# ['g', 'h', 'i']
d[0]                             # peek at leftmost item
# 'g'
d[-1]                            # peek at rightmost item
# 'i'

list(reversed(d))                # list the contents of a deque in reverse
['i', 'h', 'g']
'h' in d                         # search the deque
True
d.extend('jkl')                  # add multiple elements at once
# deque(['g', 'h', 'i', 'j', 'k', 'l'])
d.rotate(1)                      # right rotation
# deque(['l', 'g', 'h', 'i', 'j', 'k'])
d.rotate(-1)                     # left rotation
# deque(['g', 'h', 'i', 'j', 'k', 'l'])

d.clear()                        # empty the deque
d.extendleft('abc')              # extendleft() reverses the input order
# deque(['c', 'b', 'a'])
```

## List

### 展开 list

```Python
import itertools.chain.from_iterable
Contents = itertools.chain.from_iterable(list(map(filemap, fileslist)))
```

### range 中第二个元素比第一个元素小

这种情况没有任何输出

```Python
>>> for i in range(0,-2):
...     print(i)
```

### 判断一个列表为空得最佳实践

```Python
if not a:
        print "List is empty"
    #不要用len(a)来判断
```

### 如何合并两个列表

1. 不考虑顺序（原来问题不是很明确）

```Python
listone + listtwo
#linstone.extend(listtwo)也行，就是会修改listone
```

### Python 中如何复制一个列表

可以用切片的方法

```Python
new_list = old_list[:]
# or
new_list = list(old_list)
```

可以使用 copy.copy(), 比 list() 稍慢，因为它首先去查询 old_list 的数据类型

### 如何利用下标从列表中删除一个元素

1. del

```Python
a = range(10)
# [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
del a[-1]
# [0, 1, 2, 3, 4, 5, 6, 7, 8]
```

2. pop

```Python
a = ['a', 'b', 'c', 'd']
a.pop(1)
# now a is ['a', 'c', 'd']

a = ['a', 'b', 'c', 'd']
a.pop()
# now a is ['a', 'b', 'c']
```

### 如何获取 list 中包含某个元素所在的下标

```Python
>>> ["foo","bar","baz"].index('bar')
```

### 如何扁平一个二维数组

```Python
>>> import itertools
>>> list2d = [[1,2,3],[4,5,6], [7], [8,9]]
>>> merged = list(itertools.chain(*list2d))

# python >= 2.6
>>> import itertools
>>> list2d = [[1,2,3],[4,5,6], [7], [8,9]]
>>> merged = list(itertools.chain.from_iterable(list2d))
```

### 如何将一个列表切分成若干个长度相同的子序列

```Python
[l[i:i+n] for i in range(0, len(l), n)]
```

### 按照元素对 list 进行 split

```Python
[list(group) for k, group in groupby(
            splitted_list, lambda x: x == "") if not k]
# ['a', '', '', 'a', 'a'] --> [['a'], ['a', 'a']]
```

## Collections

### Counter

`Counter.most_common(n: int)`：List the n most common elements and their counts from the most common to the least. If n is None, then list all element counts.

```Python
>>> Counter('abcdeabcdabcaba').most_common(3)
[('a', 5), ('b', 4), ('c', 3)]
```

## Itertools

### itertools.groupby【把相邻的压缩】

```Python
import itertools
s = "aabbssddeeessddaassbbdds"
res = [(digit, list(group))for digit, group in itertools.groupby(s)]
for x in res:
    print(x)

# ('a', ['a', 'a'])
# ('b', ['b', 'b'])
# ('s', ['s', 's'])
# ('d', ['d', 'd'])
# ('e', ['e', 'e', 'e'])
# ('s', ['s', 's'])
# ('d', ['d', 'd'])
# ('a', ['a', 'a'])
# ('s', ['s', 's'])
# ('b', ['b', 'b'])
# ('d', ['d', 'd'])
# ('s', ['s'])
```

### itertools.permutations and combinations

```Python
from itertools import permutations, combinations
permutations('ABCD', 2) # --> AB AC AD BA BC BD CA CB CD DA DB DC
combinations('ABCD', 2) # --> AB AC AD BC BD CD
```

### itertools.product

```Python
import itertools
a = [''.join(x) for x in itertools.product('01', repeat=3)]
print(a)
# ['000', '001', '010', '011', '100', '101', '110', '111']
```

## Set

* `isdisjoint(other)`【重要！】:Return True if the set has no elements in common with other. Sets are disjoint if and only if their intersection is the empty set.
* `set <= other`:Test whether every element in the set is in other.
* `set < other`:Test whether the set is a proper subset of other, that is, set <= other and set != other.
* `set >= other`:Test whether every element in other is in the set.
* `set > other`:Test whether the set is a proper superset of other, that is, set >= other and set != other.
* `union(*others)`: set | other | ...
* `intersection(*others)`:set & other & ...
* `difference(*others)`:set - other - ...
* `symmetric_difference(other)`:set ^ other
* `copy()`:Return a shallow copy of the set.
* set 必须传入可迭代对象 set([x])【注意！】

### 多 Set 批量操作

```Python
lis = [set((0,1,3)), set((1,3))]
set.intersection(*lis)
# set([1, 3])

set.union(*lis)
# set([0, 1, 3])
```

## Sort

* 用 lst.sort() 而不是 nlst = sorted(lst)：区别在于 lst.sort() 是 in-place sort，改变 lst, sorted 会创建新 list，成本比较高。

### 按照类的成员排序

```Python
cluster_pool = sorted(cluster_pool, key=operator.attrgetter('count'), reverse=True)
```

### 字典按照键值排序

```Python
belongs_list = sorted(meta.title_belongs.items(), key=operator.itemgetter(1), reverse=True)
```

### python comparetor

```Python
def cmp_to_key(mycmp):
    'Convert a cmp= function into a key= function'
    class K:
        def __init__(self, obj, *args):
            self.obj = obj
        def __lt__(self, other):
            return mycmp(self.obj, other.obj) < 0
        def __gt__(self, other):
            return mycmp(self.obj, other.obj) > 0
        def __eq__(self, other):
            return mycmp(self.obj, other.obj) == 0
        def __le__(self, other):
            return mycmp(self.obj, other.obj) <= 0
        def __ge__(self, other):
            return mycmp(self.obj, other.obj) >= 0
        def __ne__(self, other):
            return mycmp(self.obj, other.obj) != 0
    return K
To convert to a key function, just wrap the old comparison function:

>>> sorted([5, 2, 4, 1, 3], key=cmp_to_key(reverse_numeric))
[5, 4, 3, 2, 1]
```

## Other

### 列表解析 和 map 的性能

- 函数：map 性能好一点

```
$ python -mtimeit -s'xs=range(10)' 'map(hex, xs)'
100000 loops, best of 3: 4.86 usec per loop
$ python -mtimeit -s'xs=range(10)' '[hex(x) for x in xs]'
100000 loops, best of 3: 5.58 usec per loop
```

- lambda：列表解析好一点

```
$ python -mtimeit -s'xs=range(10)' 'map(lambda x: x+2, xs)'
100000 loops, best of 3: 4.24 usec per loop
$ python -mtimeit -s'xs=range(10)' '[x+2 for x in xs]'
100000 loops, best of 3: 2.32 usec per loop
```

## Python 2.7 里 [...] 是什么？

What is this `[…]`?

```Python
[1, [...], 2]
```

它意味着你在它的内部创建了一个无限嵌套的不能打印的列表。`p`包 含一个包含 `p`的  `p`. .. 等等。`[...]` 就是一种让你知道问题的标记

## 动态条件

```Python
while any(os.path.exists(prefix + extension) for extension in extensions):
```

## 链式调用

```Python
# 返回self就好了
# 顺序是先1后2
# 结果：[1, 2]
class chain():
    def __init__(self):
        self.s = []

    def append(self, i):
        self.s.append(i)
        # 返回self
        return self

    def __str__(self):
        return str(self.s)

item = chain()
item.append(1).append(2)
print(item)
```