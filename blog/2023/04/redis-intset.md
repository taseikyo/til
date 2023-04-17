> @Date    : 2023-04-13 23:33:27
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Redis - intset （ 整数数组）

> 原文：https://blog.csdn.net/m0_51504545/article/details/117968601 2022-07-17 18:28:02 [mooddance](https://blog.csdn.net/m0_51504545)

## 一 前言

Set 是 Redis 数据类型的一种。集合中元素是唯一的，支持存储最大元素 2^64。因为是哈希表实现的，所以添加，删除，查找的复杂度都是 O (1)。

但是 Set 除了哈希表之外，还有 intset 这种实现方式。 intset 是 Redis 独特设计的一种数据结构。当需要存储的数据全是正数且元素数量不大情况下，如 -2、-1、1、2… Redis 首选 intset 作为实现方式。

## 二 源码解读

### 2.1 内存布局

在 intset.h 中定义了 intset 的结构体：

```C
typedef struct intset {
    uint32_t encoding; 
    uint32_t length;
    int8_t contents[];
} intset;
```

- encoding 编码方式。目前共支持三种范围：
    - INTSET_ENC_INT16：占用 2 个字节，存储范围为 -2^16 ~ 2^16-1。
    - INTSET_ENC_INT32：占用 4 个字节，存储范围为 -2^32 ~ 2^32-1。
    - INTSET_ENC_INT64：占用 8 个字节，存储范围为 -2^64 ~ 2^64-1。
- length 存储元素个数。
- contents 存储元素的正数数组。其元素特点是不重复且按照升序顺序排列。
    

### 2.2 操作接口

**创建集合**

```C
intset *intsetNew(void) {
    intset *is = zmalloc(sizeof(intset));  // 分配内存
    is->encoding = intrev32ifbe(INTSET_ENC_INT16);  // 默认编码为 INTSET_ENC_INT16
    is->length = 0;  // 默认长度为 0
    return is;
}
```

**添加元素**

```C
intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {

	// 判断当前插入的元素范围 获取合适的编码方式
    uint8_t valenc = _intsetValueEncoding(value);
    uint32_t pos;
    
    if (success) *success = 1;

    // 是否进行扩容操作 
    // 如当前编码方式是 INTSET_ENC_INT16， 此时需要存入的数据小于 -2^16 或大于 2^16-1， 则需要进行扩容操作。
    if (valenc > intrev32ifbe(is->encoding)) {
       
        // 执行扩容 该函数下面在讲解
        return intsetUpgradeAndAdd(is,value);
    } else {
    
       // 判断该元素是否存在集合和确定当前元素的插入点
       // 使用了二分查询
        if (intsetSearch(is,value,&pos)) {
            if (success) *success = 0;
            return is;
        }
			
		// 调整集合	
        is = intsetResize(is,intrev32ifbe(is->length)+1);
        if (pos < intrev32ifbe(is->length)) intsetMoveTail(is,pos,pos+1);
    }

	// 真正写入集合的函数。
    _intsetSet(is,pos,value);
    // 长度加一
    is->length = intrev32ifbe(intrev32ifbe(is->length)+1);
    return is;
}

// intsetSearch 函数 
// 查找给定值，若存在返回 1，pos为所在位置；若不存在返回 0，pos为可插入位置。

static uint8_t intsetSearch(intset *is, int64_t value, uint32_t *pos) {
    int min = 0, max = intrev32ifbe(is->length)-1, mid = -1;
    int64_t cur = -1;

    // 空集合直接 return
    if (intrev32ifbe(is->length) == 0) {
        if (pos) *pos = 0;
        return 0;
    } else {
        
        // 若当前值超出当前编码方式的最大值，则 pos 为末尾值。
        if (value > _intsetGet(is,max)) {
            if (pos) *pos = intrev32ifbe(is->length);
            return 0;
        } else if (value < _intsetGet(is,0)) {
        // 若当前值超出当前编码方式的最小值，则 pos 为最头部。
            if (pos) *pos = 0;
            return 0;
        }
    }
	
	// 当集合不为空 且当前值处于当前编码范围内。
	// 使用二分法进行查找，平均时间复杂度为 O(logn)。
    while(max >= min) {
        mid = ((unsigned int)min + (unsigned int)max) >> 1;
        cur = _intsetGet(is,mid);
        if (value > cur) {
            min = mid+1;
        } else if (value < cur) {
            max = mid-1;
        } else {
            break;
        }
    }

	// 若存在 则插入点就是当前位置。 
    if (value == cur) {
        if (pos) *pos = mid;
        return 1;
    } else {
      // 不存在 插入点为 min
        if (pos) *pos = min;
        return 0;
    }
}
```

**查找元素**

涉及到查找操作，如返回一个元素、判断元素是否存在、查询元素位置等操作都是调用 intsetGet -> intsetGetEncoded 函数。

```C
// 返回给定编码的 pos 位置的值。
static int64_t _intsetGetEncoded(intset *is, int pos, uint8_t enc) {
    int64_t v64;
    int32_t v32;
    int16_t v16;

    if (enc == INTSET_ENC_INT64) {
        memcpy(&v64,((int64_t*)is->contents)+pos,sizeof(v64));
        memrev64ifbe(&v64);
        return v64;
    } else if (enc == INTSET_ENC_INT32) {
        memcpy(&v32,((int32_t*)is->contents)+pos,sizeof(v32));
        memrev32ifbe(&v32);
        return v32;
    } else {
        memcpy(&v16,((int16_t*)is->contents)+pos,sizeof(v16));
        memrev16ifbe(&v16);
        return v16;
    }
}
```

**移除元素**

```C
intset *intsetRemove(intset *is, int64_t value, int *success) {
    uint8_t valenc = _intsetValueEncoding(value);
    uint32_t pos;
    if (success) *success = 0;
		
	// 当给定值处于当前集合的编码范围且存在集合当中	
    if (valenc <= intrev32ifbe(is->encoding) && intsetSearch(is,value,&pos)) {
        uint32_t len = intrev32ifbe(is->length)
        
        if (success) *success = 1;
        
        // 调整集合
        if (pos < (len-1)) intsetMoveTail(is,pos+1,pos);
        is = intsetResize(is,len-1);
        // 长度减 1
        is->length = intrev32ifbe(len-1);
    }
    return is;
}
```

**集合扩容**

Set 只有扩容操作，不能缩小。所以触犯扩容都是在添加元素时候超过了原来的编码方式。

```C
static intset *intsetUpgradeAndAdd(intset *is, int64_t value) {

	// 当前集合的编码方式
    uint8_t curenc = intrev32ifbe(is->encoding);
    // value 确定新的集合的编码方式
    uint8_t newenc = _intsetValueEncoding(value);
    
    int length = intrev32ifbe(is->length);
    // 确定数据插入的位置。
    int prepend = value < 0 ? 1 : 0;

    // 首先设置新的编码和调整大小
    is->encoding = intrev32ifbe(newenc);
    is = intsetResize(is,intrev32ifbe(is->length)+1);

   // 避免覆盖数据 采用从后往前的重编码顺序。
   // 如原有 1、2、3 使用INTSET_ENC_INT16，现在需要加入 65538 需要用 INTSET_ENC_INT32。 
    while(length--)
        _intsetSet(is,length+prepend,_intsetGetEncoded(is,length,curenc));

   // 将待添加的 value 添加到首部或者尾部, 因为是扩容所以 value 是大于原有最大值或小于最小值。
   // _intsetSet 为实际写如的逻辑。详情见源码 。
    if (prepend)
        _intsetSet(is,0,value);
    else
        _intsetSet(is,intrev32ifbe(is->length),value);
    is->length = intrev32ifbe(intrev32ifbe(is->length)+1);
    return is;
}
```

### 三 总结

intset 是 Set 除哈希表外的一种实现方式，当所有数据为正数时候 Redis 会采用 intset。intset 实现上相对其他的数据结构是比较简单的。
