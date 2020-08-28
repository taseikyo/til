> @Date    : 2020-08-27 22:40:27
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 五种排序算法的 C++ 实现以及时间分析

今天晚上逛 GitHub 看到这么一个项目 [dta0502/Sort-Compare](https://github.com/dta0502/Sort-Compare)，他用 Python 实现了五种常见的排序算法并进行比较，感觉很有意思，于是用 C++ 实现了一遍。

## Table of Contents

- [实验结果](#实验结果)
- [选择排序](#选择排序)
- [插入排序](#插入排序)
- [归并排序](#归并排序)
- [快速排序](#快速排序)
- [堆排序](#堆排序)

## 实验结果

所有代码都在 [comparison.cpp](comparison.cpp) 中，`TEST_TIMES` 指定了每个排序函数的测试次数，`MAX_SIZE` 是排序的数组的大小，测试结果如下：

TEST_TIMES：1<<15，MAX_SIZE：100

| 排序算法 | 时间  |
|:--------:|-------|
| quick    | 0.122 |
| heap     | 0.425 |
| merge    | 0.771 |
| select   | 0.859 |
| insert   | 1.131 |

TEST_TIMES：1<<15，MAX_SIZE：500

| 排序算法 | 时间   |
|:--------:|--------|
| quick    | 1.264  |
| heap     | 2.991  |
| merge    | 4.598  |
| select   | 17.441 |
| insert   | 24.658 |

TEST_TIMES：1<<15，MAX_SIZE：1000

| 排序算法 | 时间   |
|:--------:|--------|
| quick    | 2.981  |
| heap     | 6.712  |
| merge    | 10.007 |
| select   | 73.314 |
| insert   | 104.41 |

总结：快速排序永远滴神！

## 选择排序

### 原理

首先，找到数组中最小的那个元素，将它和数组的第一个元素交换位置（如果第一个元素就是最小元素那么它就和自己交换）。再次，在剩下的元素中找到最小的元素，将它与数组的第二个元素交换位置。如此往复，直到将整个数组排序。这种方法叫做选择排序，因为它在不断地选择剩余元素之中的最小者。

![](../../images/选择排序.gif)

### 实现

```C++
void selection_sort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		int idx = i;
		for (int j = i + 1; j < n; ++j) {
			if (nums[j] < nums[idx]) {
				idx = j;
			}
		}
		swap(nums[i], nums[idx]);
	}
}
```

## 插入排序

### 原理

通常人们整理桥牌的方法是一张一张的来，将每一张牌插入到其他已经有序的牌中的适当位置。在计算机的实现中，为了给要插入的元素腾出空间，我们需要将其余所有元素在插入之前都向右移动一位。这种算法叫做插入排序。

![](../../images/插入排序.gif)

### 实现

```C++
void insertion_sort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 1; i < n; ++i) {
		int j = i - 1;
		for (; j >= 0; --j) {
			if (nums[j] <= nums[j + 1]) {
				break;
			}
			swap(nums[j], nums[j + 1]);
		}
	}
}
```

## 归并排序

### 原理

归并排序体现的是一种分治思想（Divide and conquer）

1. 将数组一分为二（Divide array into two halves），对每部分进行递归式地排序（Recursively sort each half）
2. 合并两个部分（Merge two halves）

![](../../images/归并排序.gif)

### 实现

```C++
void merge(vector<int>& nums, int st, int mid, int ed) {
	vector<int> tmp(ed - st + 1, 0);
	int l = st, r = mid + 1, i = 0;
	while (l <= mid && r <= ed) {
		if (nums[l] < nums[r]) {
			tmp[i++] = nums[l++];
		} else {
			tmp[i++] = nums[r++];
		}
	}
	while (l <= mid) {
		tmp[i++] = nums[l++];
	}
	while (r <= ed) {
		tmp[i++] = nums[r++];
	}
	for (int i = 0; i < ed - st + 1; ++i) {
		nums[st + i] = tmp[i];
	}
}

void merge_sort(vector<int>& nums, int st, int ed) {
	if (st >= ed) {
		return;
	}
	int mid = st + (ed - st) / 2;
	merge_sort(nums, st, mid);
	merge_sort(nums, mid + 1, ed);
	merge(nums, st, mid, ed);
}

void merge_sort(vector<int>& nums) {
	merge_sort(nums, 0, nums.size() - 1);
}
```

## 快速排序

### 原理

快速排序是一种分治的排序算法。它将一个数组分成两个子数组，将两部分独立地排序。

快速排序和归并排序是互补的：

归并排序：
	1. 将数组分成两个子数组分别排序，并将有序的子数组归并以将整个数组排序；
	2. 递归调用发生在处理整个数组之前；
	3. 一个数组被等分为两半。

快速排序：
	1. 则是当两个子数组都有序时，整个数组也就自然有序了；
	2. 递归调用发生在处理整个数组之后；
	3. 切分（partition）的位置取决于数组的内容。

![](../../images/快速排序.gif)

## 实现

```C++
void quick_sort(vector<int>& nums, int l, int r) {
	if (l < r) {
		int i = l, j = r, x = nums[l];
		while (i < j) {
			while (i < j && nums[j] >= x) j--;
			if (i < j) nums[i++] = nums[j];
			while (i < j && nums[i] < x) i++;
			if (i < j) nums[j--] = nums[i];
		}
		nums[i] = x;
		quick_sort(nums, l, i - 1);
		quick_sort(nums, i + 1, r);
	}
}

void quick_sort(vector<int>& nums) {
	quick_sort(nums, 0, nums.size() - 1);
}
```

## 堆排序

### 原理

堆排序可以分成两个阶段。在堆的构造阶段中，我们将原始数组重新组织安排进一个堆中；然后在下沉排序阶段，我们从堆中按递减顺序取出所有元素并得到排序结果。

### 实现

```C++
void heapify(vector<int>& v, int st, int ed) {
	int dad = st;
	int son = dad * 2 + 1;
	while (son <= ed) {
		if (son + 1 <= ed && v[son] < v[son + 1]) son++;
		if (v[dad] > v[son]) return;
		else {
			swap(v[dad], v[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(vector<int>& v) {
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, 0, i - 1);
	}
}
```