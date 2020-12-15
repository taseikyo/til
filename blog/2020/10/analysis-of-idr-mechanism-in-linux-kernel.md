> @Date    : 2020-10-25 16:05:41
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 浅析 Linux 内核中的 idr 机制

> 原文：http://blog.sina.com.cn/s/blog_476d8cf30100nhfc.html 作者：[长夜未央](http://blog.sina.com.cn/ap0304118) 2010-11-11 09:42:09 

## Table of Contents

- [(1) 获得 idr](#(1)-获得-idr)
- [(2) 为 idr 分配内存](#(2)-为-idr-分配内存)
- [(3) 分配 ID 号并将 ID 号和指针关联](#(3)-分配-id-号并将-id-号和指针关联)
- [(4) 通过 ID 号搜索对应的指针](#(4)-通过-id-号搜索对应的指针)
- [(5) 删除 ID](#(5)-删除-id)
- [实际应用](#实际应用)

idr 在 Linux 内核中指的就是整数 ID 管理机制，从本质上来说，这就是一种将整数 ID 号和特定指针关联在一起的机制。这个机制最早是在 2003 年 2 月加入内核的，当时是作为 POSIX 定时器的一个补丁。现在，在内核的很多地方都可以找到 idr 的身影。

idr 机制适用在那些需要把某个整数和特定指针关联在一起的地方。举个例子，在 I2C 总线中，每个设备都有自己的地址，要想在总线上找到特定的设备，就必须要先发送该设备的地址。如果我们的 PC 是一个 I2C 总线上的主节点，那么要访问总线上的其他设备，首先要知道他们的 ID 号，同时要在 pc 的驱动程序中建立一个用于描述该设备的结构体。

此时，问题来了，我们怎么才能将这个设备的 ID 号和他的设备结构体联系起来呢？最简单的方法当然是通过数组进行索引，但如果 ID 号的范围很大（比如 32 位的 ID 号），则用数组索引显然不可能；第二种方法是用链表，但如果网络中实际存在的设备较多，则链表的查询效率会很低。遇到这种清况，我们就可以采用 idr 机制，该机制内部采用 radix 树实现，可以很方便地将整数和指针关联起来，并且具有很高的搜索效率。

## (1) 获得 idr

要在代码中使用 idr，首先要包括 `<linux/idr.h>`。接下来，我们要在代码中分配 idr 结构体，并初始化：

```C
void idr_init(struct idr *idp);
```

其中 idr 定义如下：

```C
struct idr {
	struct idr_layer *top;
	struct idr_layer *id_free;
	int               layers;
	int               id_free_cnt;
	spinlock_t        lock;
};
```

## (2) 为 idr 分配内存

```C
int idr_pre_get(struct idr *idp, unsigned int gfp_mask);
```

每次通过 idr 获得 ID 号之前，需要先分配内存。返回 0 表示错误，非零值代表正常

## (3) 分配 ID 号并将 ID 号和指针关联

```C
int idr_get_new(struct idr *idp, void *ptr, int *id);
int idr_get_new_above(struct idr *idp, void *ptr, int start_id, int *id);
```

- idp: 之前通过 idr_init 初始化的 idr 指针
- ptr: 和 ID 号相关联的指针
- id:  由内核自动分配的 ID 号
- start_id: 起始 ID 号。内核在分配 ID 号时，会从 start_id 开始。如果为 I2C 节点分配 ID 号，可以将设备地址作为 start_id

函数调用正常返回 0，如果没有 ID 可以分配，则返回 `-ENOSPC`

在实际中，上述函数常常采用如下方式使用：

```C
again:
	if (idr_pre_get(&my_idr, GFP_KERNEL) == 0) {
		/* No memory, give up entirely */ 
	}
	spin_lock(&my_lock);
	result = idr_get_new(&my_idr, &target, &id);
	if (result == -EAGAIN) {
		sigh();
		spin_unlock(&my_lock);
		goto again;
	}
```

## (4) 通过 ID 号搜索对应的指针

```C
void *idr_find(struct idr *idp, int id);
```

返回值是和给定 id 相关联的指针，如果没有，则返回 NULL

## (5) 删除 ID

要删除一个 ID，使用：

```C
void idr_remove(struct idr *idp, int id);
```

## 实际应用

通过上面这些方法，内核代码可以为子设备，inode 生成对应的 ID 号。这些函数都定义在 `<linux-2.6.xx/lib/idr.c>` 中

下面，我们通过分析 I2C 协议的核心代码，来看一看 idr 机制的实际应用：

```C
< linux - 2.6.23 / drivers / i2c / i2c - core.c >
...
< linux / idr.h > /* idr头文件 */
...
static DEFINE_IDR(i2c_adapter_idr); /* 声明idr */
...
/*
  采用动态总线号声明并注册一个i2c适配器(adapter)，可睡眠
  针对总线号可动态指定的设备，如基于USB的i2c设备或pci卡
 */
int i2c_add_adapter(struct i2c_adapter *adapter) {
	int     id, res = 0;
retry:
	if (idr_pre_get(&i2c_adapter_idr, GFP_KERNEL) == 0)
		return -ENOMEM;
	mutex_lock(&core_lists);
	/* __i2c_first_dynamic_bus_num是当前系统允许的动态总线号的最大值 */
	res = idr_get_new_above(&i2c_adapter_idr, adapter, __i2c_first_dynamic_bus_num, &id);
	mutex_unlock(&core_lists);
	if (res < 0) {
		if (res == -EAGAIN)
			goto retry;
		return res;
	}
	adapter->nr = id;
	return i2c_register_adapter(adapter);
}
EXPORT_SYMBOL(i2c_add_adapter);

/*
  采用静态总线号声明并注册一个i2c适配器(adapter)
 */
int i2c_add_numbered_adapter(struct i2c_adapter *adap) {
	int     id;
	int     status;
	if (adap->nr & ~MAX_ID_MASK)
		return -EINVAL;
retry:
	if (idr_pre_get(&i2c_adapter_idr, GFP_KERNEL) == 0)
		return -ENOMEM;
	mutex_lock(&core_lists);
	/* "above" here means "above or equal to", sigh;
	 * we need the "equal to" result to force the result
	 */
	status = idr_get_new_above(&i2c_adapter_idr, adap, adap->nr, &id);
	if (status == 0 && id != adap->nr) {
		status = -EBUSY;
		idr_remove(&i2c_adapter_idr, id);
	}
	mutex_unlock(&core_lists);
	if (status == -EAGAIN)
		goto retry;
	if (status == 0)
		status = i2c_register_adapter(adap);
	return status;
}
EXPORT_SYMBOL_GPL(i2c_add_numbered_adapter);

/* 注销一个i2c适配器 */
int i2c_del_adapter(struct i2c_adapter *adap) {
	...
	/* free bus id */
	idr_remove(&i2c_adapter_idr, adap->nr);
	...
	return res;
}
EXPORT_SYMBOL(i2c_del_adapter);

/* 通过ID号获得i2c_adapter设备结构体 */
struct i2c_adapter* i2c_get_adapter(int id) {
	struct i2c_adapter *adapter;
	mutex_lock(&core_lists);
	adapter = (struct i2c_adapter *)idr_find(&i2c_adapter_idr, id);
	if (adapter && !try_module_get(adapter->owner))
		adapter = NULL;
	mutex_unlock(&core_lists);
	return adapter;
}
EXPORT_SYMBOL(i2c_get_adapter);
```
