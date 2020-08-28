> @Date    : 2020-08-28 10:20:46
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/qq_26399665/article/details/79831490)

# 1. 背景

笔试时，遇到一个算法题：差不多是 在 n 个不同的数中随机取出不重复的 m 个数。洗牌算法是将原来的数组进行打散，使原数组的某个数在打散后的数组中的每个位置上等概率的出现，刚好可以解决该问题。

# 2. 洗牌算法

由抽牌、换牌和插牌衍生出三种洗牌算法，其中抽牌和换牌分别对应 Fisher-Yates Shuffle 和 Knuth-Durstenfeld Shhuffle 算法。

## 2.1 Fisher-Yates Shuffle 

最早提出这个洗牌方法的是 Ronald A. Fisher 和 Frank Yates，即 Fisher–Yates Shuffle，其基本思想就是从原始数组中随机取一个之前没取过的数字到新的数组中，具体如下：  

1. 初始化原始数组和新数组，原始数组长度为 n(已知)；  
2. 从还没处理的数组（假如还剩 k 个）中，随机产生一个 [0, k) 之间的数字 p（假设数组从 0 开始）；  
3. 从剩下的 k 个数中把第 p 个数取出；  
4. 重复步骤 2 和 3 直到数字全部取完；  
5. 从步骤 3 取出的数字序列便是一个打乱了的数列。

下面证明其随机性，即每个元素被放置在新数组中的第 i 个位置是 1/n（假设数组大小是 n）。  

  证明：一个元素 m 被放入第 i 个位置的概率 P = 前 i-1 个位置选择元素时没有选中 m 的概率 * 第 i 个位置选中 m 的概率，即

$$
\begin{array}{l}
P_i=\frac{n-1}{n} \times \frac{n-2}{n-1} \times \ldots \times \frac{n-1+1}{n-i+2} \times \frac{1}{n-i+1} \\
=\frac{1}{n}
\end{array}
$$


```C++
#define N 10
#define M 5
void Fisher_Yates_Shuffle(vector<int>& arr,
                          vector<int>& res) {
	srand((unsigned)time(NULL));
	int k;
	for (int i = 0; i < M; ++i) {
		k = rand() % arr.size();
		res.push_back(arr[k]);
		arr.erase(arr.begin() + k);
	}
}
```

时间复杂度为 O(n^2)，空间复杂度为 O(n)

## 2.2 Knuth-Durstenfeld Shuffle

Knuth 和 Durstenfeld  在 Fisher 等人的基础上对算法进行了改进，在原始数组上对数字进行交互，省去了额外 O(n) 的空间。该算法的基本思想和 Fisher 类似，每次从未处理的数据中随机取出一个数字，然后把该数字放在数组的尾部，即数组尾部存放的是已经处理过的数字。

算法步骤为：

1. 建立一个数组大小为 n 的数组 arr，分别存放 1 到 n 的数值；  
2. 生成一个从 0 到 n - 1 的随机数 x；  
3. 输出 arr 下标为 x 的数值，即为第一个随机数；  
4. 将 arr 的尾元素和下标为 x 的元素互换；  
5. 同 2，生成一个从 0 到 n - 2 的随机数 x；  
6. 输出 arr 下标为 x 的数值，为第二个随机数；  
7. 将 arr 的倒数第二个元素和下标为 x 的元素互换；  

如上，直到输出 m 个数为止该算法是经典洗牌算法。它的证明如下：

对于 arr[i]，洗牌后在第 n-1 个位置的概率是 1/n（第一次交换的随机数为 i），在 n-2 个位置概率是 [(n-1)/n] * [1/(n-1)] = 1/n，（注意，若 i=n-1，第一交换 arr[n-1]会被换到一个随机的位置），在第 n-k 个位置的概率是 [(n-1)/n] * [(n-2)/(n-1)] * ... * [(n-k+1)/(n-k+2)] * [1/(n-k+1)] = 1/n

（第一个随机数不要为 i，第二次不为 arr[i] 所在的位置 (随着交换有可能会变)...第 n-k 次为 arr[i] 所在的位置）

```C++
void Knuth_Durstenfeld_Shuffle(vector<int>&arr) {
	for (int i = arr.size() - 1; i >= 0; --i) {
		srand((unsigned)time(NULL));
		swap(arr[rand() % (i + 1)], arr[i]);
	}
}
```

时间复杂度为 O(n), 空间复杂度为 O(1), 缺点必须知道数组长度 n

原始数组被修改了，这是一个原地打乱顺序的算法，算法时间复杂度也从 Fisher 算法的 O(n^2) 提升到了 O(n)。由于是从后往前扫描，无法处理不知道长度或动态增长的数组。  

## 2.3 Inside-Out Algorithm

Knuth-Durstenfeld Shuffle 是一个内部打乱的算法，算法完成后原始数据被直接打乱，尽管这个方法可以节省空间，但在有些应用中可能需要保留原始数据，所以需要另外开辟一个数组来存储生成的新序列。

Inside-Out Algorithm 算法的基本思思是从前向后扫描数据，把位置 i 的数据随机插入到前 i 个（包括第 i 个）位置中（假设为 k），这个操作是在新数组中进行，然后把原始数据中位置 k 的数字替换新数组位置 i 的数字。其实效果相当于新数组中位置 k 和位置 i 的数字进行交互。

如果知道 arr 的长度的话，可以改为 for 循环，由于是**从前往后遍历，所以可以应对 arr[] 数目未知的情况，或者 arr[] 是一个动态增加的情况**。

证明如下：

原数组的第 i 个元素（随机到的数）在新数组的前 i 个位置的概率都是：(1/i) * [i/(i+1)] * [(i+1)/(i+2)] * ... * [(n-1)/n] = 1/n，（即第 i 次刚好随机放到了该位置，在后面的 n-i 次选择中该数字不被选中）。

原数组的第 i 个元素（随机到的数）在新数组的 i+1 （包括 i + 1）以后的位置（假设是第 k 个位置）的概率是：(1/k) * [k/(k+1)] * [(k+1)/(k+2)] * ... * [(n-1)/n] = 1/n（即第 k 次刚好随机放到了该位置，在后面的 n-k 次选择中该数字不被选中）。

```C++
void Inside_Out_Shuffle(const vector<int>&arr,
                        vector<int>& res) {
	res.assign(arr.size(), 0);
	copy(arr.begin(), arr.end(), res.begin());
	int k;
	for (int i = 0; i < arr.size(); ++i) {
		srand((unsigned)time(NULL));
		k = rand() % (i + 1);
		res[i] = res[k];
		res[k] = arr[i];
	}
}
```

时间复杂度为 O(n), 空间复杂度为 O(n)

## 2.4 蓄水池抽样

从 N 个元素中随机等概率取出 m 个元素，N 长度未知。它能够在 O(n) 时间内对 n 个数据进行等概率随机抽取。**如果数据集合的量特别大或者还在增长（相当于未知数据集合总量），该算法依然可以等概率抽样.**

```C++
void Reservoir_Sampling(vector<int>& arr) {
	int k;
	for (int i = m; i < arr.size(); ++i) {
		srand((unsigned)time(NULL));
		k = rand() % (i + 1);
		if (k < m) swap(arr[k], arr[i]);
	}
}
```

算法思路大致如下：

1. 如果接收的数据量小于 m，则依次放入蓄水池
2. 当接收到第 i 个数据时，i >= m，在 [0, i] 范围内取以随机数 k，若 k 的落在 [0, m-1] 范围内，则用接收到的第 i 个数据替换蓄水池中的第 k 个数据
3. 重复步骤2

算法的精妙之处在于：当处理完所有的数据时，蓄水池中的每个数据都是以 m/n 的概率获得的。

第 i 个对象被选中的概率 = 选择 i 的概率 * （其后元素不被选择的概率 + 其后元素被选择的概率 * 不替换第 i 个对象的概率）

$$
\begin{array}{l}
P_i=\frac{m}{i} \times\left[\left(\frac{i+1-m}{i+1}+\frac{m}{i+1} \times \frac{m-1}{m}\right) \times\left(\frac{i+2-m}{i+2}+\frac{m}{i+2} \times \frac{m-1}{m}\right) \times \ldots \times\left(\frac{n-\mathrm{m}}{n}+\frac{m}{n} \times \frac{m-1}{m}\right)\right] \\
=\frac{m}{i} \times \frac{i}{n} \\
=\frac{m}{n}
\end{array}
$$

## 2.5 分布式蓄水池抽样

- https://www.jianshu.com/p/eea05fb27e3f

一道电面题目, 分为两问:

1. 设计一个系统，不断接收数据包 (数据内容可以简单想成一个 int 值). 给定常量 M，要求从所有获取的数据中随机抽样 M 个，每个样本被抽取的概率相等
	* 如果已接收数据包的数量还未超过 M 个，则将它们全部返回
	* 接收数据包的总量是未知的，可能非常大
	* 机器的存储空间有限，无法存储所有数据包. 但是存储 M 个数据包还是绰绰有余的
2. 假如有 K 台机器，如何将第一问的算法做成分布式的，以最大化吞吐量？

### 第一问是一个标准的水塘抽样算法 (Reservoir Sampling) 问题

```C++
class System {
  private:
	vector<int> v;
	int capacity;
	int cnt;
  public:
	System(int capacity) : capacity(capacity), cnt(0) {}
	void put(int n) {
		++cnt;
		if (cnt <= capacity) {
			v.push_back(n);
			return;
		}
		int index = rand() % cnt;
		if (index < capacity) {
			v[index] = n;
		}
	}
	vector<int> get() {
		return v;
	}
};
```

算法思路:  

维护一个大小为 `M` 的数组。记当前接收的是第 `N` 个数据 (从 `1` 开始)

* 如果 `N<=M`，直接插入
* 如果 `N>M`，就取一个 `1~N` 之间的随机数 `index`。如果 `index` 在 `1~M` 之间，则用新接收的数据替换第 `index` 个数据; 否则丢弃.

### 第二问就是分布式的蓄水池抽样问题了

算法思路是:

假设有 `K` 个机器，每个机器维护大小为 `M` 的数组，并记录该机器接受的数据总数 `Ni`

* 当机器获取新数据时，进行单机的蓄水池抽样
* 当进行采样时，重复 `M` 次以下操作:  
    * 取随机数 `d` 在 `[0,1)` 之间，记 `N=Sum(Ni | i=1...K)`
    * 若 `d<N1/N` 则从第一个机器上等概率抽取一个元素
    * 若 `N1/N<=d<(N1+N2)/N` 则从第二个机器上等概率抽取一个元素
    * 依此类推

假设 `Ni>M`：

因为第 `i` 个机器上数据的留存概率为 `M/Ni`，而采样时又以 `Ni/N` 的概率抽取该机器，又以 `1/M` 的概率等概率**不放回**地选取一个元素，所以第 `i` 个机器上一个数据被抽中的概率为 `M/Ni * Ni/N * 1/M = 1/N`。这样重复 `M` 次，每个元素被抽取到的概率就是 `M/N`

假设 `Ni<=M`：

第 `i` 个机器上数据的留存概率为 `1`，采样时以 `Ni/N` 的概率抽取该机器，又以 `1/Ni` 的概率等概率**不放回**地选取一个元素，所以第 `i` 个机器上一个数据被抽中的概率为 `1/N`。同样, 重复 `M` 次让每个元素被抽取到的概率为 `M/N`。