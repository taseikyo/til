> @Date    : 2020-09-09 15:19:15
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 每日一题

记录看到的有趣的题目，不一定会每天更新 :3

## Table of Contents

- [int 数组求平均数](#int-数组求平均数)
	- [200909-解答](#200909-解答)
- [最小编辑代价](#最小编辑代价)
	- [200910-解答](#200910-解答)

## int 数组求平均数

- https://www.nowcoder.com/discuss/81769

一道面试题，题意如下：

```
给一个 int 数组，求平均数，返回值为 int 型。数组长度可能会很长，累加过程中可能会超出 int 范围，不能用long，double，怎么做？
```

### 200909-解答

本来我是想用分治，然后发现并没有那么简单，在计算的时候会丢失余数。

帖子下面有人给出了解答，原来这个题目时 Quora 上的。

- [C++ 代码](src/get_average.cpp)

楼主思路是对的，但是写得复杂了，关键就是现有余数 `r` 和新的余数 `a[i] % N` 合并这步，可以直接判断相加后是否大于 N，因为 `r` 和 `a[i] % N` 的范围都是左闭右开区间 `[0, N)` ，因此 `N-r` 和 `a[i] % N` 的范围也是 `[0, N)` ，比较大小即可。

```C
int get_average(vector<int> a) {
	int n = a.size();
	int aver = 0;
	int rest = 0;  // [0, n)
	for (int i = 0; i < n; ++i) {
		aver += a[i] / n;
		int temp = a[i] % n;
		if (temp < 0) {
			temp += n;
			aver -= 1;
		}
		// rest + temp > n，防止溢出
		if (rest > n - temp) {
			aver++;
			rest -= (n - temp);
		} else {
			rest += temp;
		}
	}
	// 假定负数结果向0取整
	return (aver >= 0) ? aver : aver + 1;
}
```

思路参考 [Quora 上的问答](https://www.quora.com/How-can-I-compute-the-average-of-a-large-array-of-integers-without-running-into-overflow)，但是原回答包括楼主的做法都有一点没考虑到，那就是负数是否向 0 取整的问题。  
比如 `-25 / 9` 和 `-25 % 9` 的值，在 C/C++/Java 这种语言中，结果分别是 - 2 和 - 7，而在中间处理时，合适的结果应该是 - 3 和 2，否则会出问题。

比如楼主的程序对 `{-10, 3, 9}` 结果是 1，对 `{-10, 3, 8}` 结果是 0，对 `{-10, 3, 7}` 的结果是 -1。原答案的程序对 `{-10, 3, 9}` 结果是 1，对 `{-10, 3, 8}` 结果是 0，对 `{-10, 3, 7}` 的结果是 0。但如果最后结果需要负数向 0 取整的话，还要再判断结果是否为负数，若为负数，则需要加 1。

另外，对于输入是数据流而非固定数组的情况，稍微就有点麻烦。  
设 `x(k)` 和 `r(k)` 依次是数组 `a[1..k]` （为方便，下标从 1 开始）的平均值（取整）和余数。那么有

```C
x(k+1) = (k * x(k) + r(k) + a[k+1]) / (k+1)
       = x(k) + (r(k) + a[k+1] - x(k)) / (k+1)
r(k+1) = (r(k) + a[k+1] - x(k)) % (k+1)
```

关键就是在不溢出的情况下求 `(r(k) + a[k+1] - x(k)) / (k+1)`，相当于求大小为 3 的数组 `{r(k), a[k+1], -x(k)}` 的加权平均值，不过权重不是 `1/3` 而是 `1/(k+1)`。  
看似如此，实际上 `-x(k)` 可能溢出，因为 `INT_MAX` 的绝对值比 `INT_MIN` 的绝对值小 1，所以 `x(k)` 是 `INT_MIN` 即 `0x80000000` 的时候， `-x(k)` 仍然是 `0x80000000` ，溢出。

至于数据流特别大，也就是说元素数量 k 超过了 int 的范围的话，考虑就更为复杂了。

## 最小编辑代价

- https://www.nowcoder.com/questionTerminal/05fed41805ae4394ab6607d0d745c8e4

一道面试题，快手跟字节都出过，如下：

```
给定两个字符串str1和str2，再给定三个整数ic，dc和rc，分别代表插入、删除和替换一个字符的代价，请输出将str1编辑成str2的最小代价。

输入
"abc","adc",5,3,2

输出
2

输入
"abc","adc",5,3,100

输出
8
```

### 200910-解答

leetcode 有类似的题目（[72.编辑距离](https://leetcode-cn.com/problems/edit-distance/)），不过没有代价区分，增删改代价都是 1。

所以这个题看上去更有意思，解答来自：https://www.cnblogs.com/flix/p/13596911.html

- [C++ 代码](src/min_edit_cost.cpp)

- 状态定义：dp[i][j] 表示 str[0,...,i-1] 到 str[0,...,j-1] 的最小代价；
- 状态转移：dp[i][j] 可以从 dp[i-1][j]、dp[i][j-1] 和 dp[i-1][j-1] 转化而来，我们设置 3 个变量
	1. a = dp[i-1][j] + dc
	2. b = dp[i][j-1] + ic
	3. c 从 dp[i-1][j-1] 推导而来，当 str1[i-1]==str2[j-1] 时，c = dp[i-1][i-1]，否则 c = dp[i-1][j-1] + rc
- dp[i][j] = min(a, b, c)
- 边界条件：dp[0][j] = ic * j 表示要向 str1 中插入 j 个字符，dp[i][0] = dc * j，表示要删除 str1 的 i 个字符。

- 时间复杂度：O(m * n)
- 空间复杂度：O(m * n)
