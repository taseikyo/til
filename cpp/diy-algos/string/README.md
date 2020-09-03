> @Date    : 2020-09-03 16:20:35
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 实现一个 string 类

## 实现

使用 C++ 实现一个 string 类（构造函数、拷贝构造函数、析构函数和字符串赋值函数等等）

`tstring` 定义如下所示，具体实现见 `tstring.cpp`

```C++
class tstring {
	friend std::ostream& operator<<(std::ostream &out,
	                                const tstring &str);
  public:
	size_t size() const;
	const char* c_str() const;
	// default constructor
	tstring(const char *str = nullptr);
	// copy constructor
	tstring(const tstring &str);
	// move constructor
	tstring(tstring &&str) noexcept;
	// assignment operator
	tstring& operator=(const tstring &str);
	// move assignment operator
	tstring& operator=(tstring &&str) noexcept;
	// [] operator
	char& operator[] (size_t idx);
	// destructor
	~tstring();
  private:
	char* tstr;
	size_t tsize;
};
```

## 测试

简单测试了下，貌似没问题

```C++
int main(int argc, char* argv[]) {
	tstring a("abcxyz123");
	tstring b;
	b = a;
	tstring c(b);
	tstring d(move(tstring("taseikyo")));
	tstring e;
	e = move(c);
	cout << "a " << a << endl;
	cout << "b " << b << endl;
	cout << "c " << c << endl;
	cout << "d " << d << endl;
	cout << "e " << e << endl;
	e[2] = '*';
	e[754] = '+';
	for (int i = 0; i < e.size(); ++i) {
		cout << e[i] << " ";
	}
	cout << endl;
	return 0;
}
```

输出如下：

```bash
λ a.exe
constructor called!
constructor called!
assignment operator called!
copy constructor called!
constructor called!
move constructor called!
constructor called!
move assignment operator called!
a 10 abcxyz123
b 10 abcxyz123
c empty tstring!
d 9 taseikyo
e 10 abcxyz123
+ b * x y z 1 2 3
```
