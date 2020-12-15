> @Date    : 2020-06-03 15:35:46
> @Author  : Lewis Tian (taseikyo@gmail.com)
> @Link    : github.com/taseikyo

## C++ Vector 的遍历

```c++
// definition
std::vector<int> v;
```


1. 传统的数组写法

```c++
for (size_t i = 0; i < v.size(); i++) {
	std::cout << v[i] << std::endl;
}
```

2. 迭代器

```c++
for (std::vector<int>::iterator it = v.begin(); it != v.end();
        ++it) {
	std::cout << *it << std::endl;
}
```

3. C++ 11 auto

```c++
for (auto it : v) {
	std::cout << it << std::endl;
}
```