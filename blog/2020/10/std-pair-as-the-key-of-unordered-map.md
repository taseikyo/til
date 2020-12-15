> @Date    : 2020-10-28 22:33:45
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# std::pair 作为 unordered_map 的 key

> 原文：https://blog.csdn.net/sinat_35261315/article/details/76473867 [一个程序渣渣的小后院](https://me.csdn.net/sinat_35261315)  2017-07-31 23:06:56

使用 pair 作为 unordered_map 的 key 时会提示这样的错误：`The C++ Standard doesn’t provide a hash for this type.`

意思是 C++ 标准中没有为 pair 提供 hash 函数，所以在使用的时候需要人为传入一个

pair 作为 unordered_map 的 key 需要为 pair 添加 hash 函数

```C
class ListNode;

struct pair_hash {
	template<class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1> {}(p.first);
		auto h2 = std::hash<T2> {}(p.second);
		return h1 ^ h2;
	}
};

unordered_map<pair<ListNode *, bool>, int> error_hash; //error
unordered_map<pair<ListNode *, bool>, int, pair_hash> ok_hash; //ok
```
