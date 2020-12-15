> @Date    : 2020-08-28 09:00:32
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 子类重载一个操作符时，如何调用父类重载的操作符？

这是 zz 面 tx cdg 的一个题，场景如下，父类 A 重载了 "==" 操作符，子类 B 继承 A 类，那么 B 中如何调用 "==" 操作符，A 和 B 都有各自的私有数据成员。

知道就很简单，不知道还挺麻烦的，简而言之就是使用 static_cast 将传进的一个参数转换为父类类型，然后直接调用父类重载的操作符即可，如下所示，A 中重载了三个操作符，在 B 中调用时，都先将 `rhs` 转化为 A 类型，然后直接调用 A 中对应的操作符，然后 B 负责自身的数据成员。

```C++
class A {
  public:
	A(): x1(0), x2('A') {}
	A(int x, char y) : x1(x), x2(y) {}
	~A() {}
	bool operator==(const A& rhs) {
		return x1 == rhs.x1 && x2 == rhs.x2;
	}
	A& operator=(const A& rhs) {
		x1 = rhs.x1;
		x2 = rhs.x2;
		return *this;
	}
	friend ostream& operator<<(ostream &os, const A& rhs) {
		os << "x1: " << rhs.x1 << " x2: " << rhs.x2;
		return os;
	}
  private:
	int x1;
	char x2;
};

class B : public A {
  public:
	B(): A(), y1(-1), y2('B') {}
	B(int a, char b) : A(a - 1, b - 1), y1(a), y2(b) {}
	~B() {}
	bool operator==(const B& rhs) {
		return y1 == rhs.y1 && y2 == rhs.y2
		       && A::operator==(static_cast<A>(rhs));
	}
	B& operator=(const B& rhs) {
		A::operator=(static_cast<A>(rhs));
		y1 = rhs.y1;
		y2 = rhs.y2;
		return *this;
	}
	friend ostream& operator<<(ostream &os, const B& rhs) {
		os << static_cast<A>(rhs);
		os << " y1: " << rhs.y1 << " y2: " << rhs.y2;
		return os;
	}
  private:
	int y1;
	char y2;
};

int main(int argc, char* argv[]) {
	A a1, a2;
	B b1(20, 'M'), b2(22, 'N');
	cout << "a1: " << a1 << endl;
	cout << "a2: " << a2 << endl;
	cout << "a1 == a2? " << (a1 == a2) << endl;
	cout << "b1: " << b1 << endl;
	cout << "b2: " << b2 << endl;
	cout << "b1 == b2? " << (b1 == b2) << endl;
	return 0;
}
```
