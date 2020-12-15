> @Date    : 2020-09-04 10:04:06
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 模板类的声明与定义分开的问题

今天在手动实现一个 `shared_ptr` 模板类中遇到这个问题，将声明与定义放在两个文件（"tshared_ptr.hpp" 和 "tshared_ptr.cpp"），结果编译出错，无论是 `g++` 还是 `clang++` 都不行，后来放到一起就编译过了。后来搜到这篇 C++ 的FAQ：
[[35.12] Why can't I separate the definition of my templates class from its declaration and put it inside a .cpp file?](http://www.cs.technion.ac.il/users/yechiel/c++-faq/templates-defn-vs-decl.html)

If all you want to know is *how* to fix this situation, read the [next](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl.html "[35.13] How can I avoid linker errors with my template functions?") [two](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl-export-keyword.html "[35.14] How does the C++ keyword export help with template linker errors?") FAQs. But in order to understand *why* things are the way they are, first accept these facts:

1. A template is not a class or a function. A template is a "pattern" that the compiler uses to generate a family of [classes](http://www.cs.technion.ac.il/users/yechiel/c++-faq/class-templates.html "[35.2] What's the syntax / semantics for a 'class template'?") or [functions](http://www.cs.technion.ac.il/users/yechiel/c++-faq/fn-templates.html "[35.3] What's the syntax / semantics for a 'function template'?").
2. In order for the compiler to generate the code, it must see both the template definition (not just declaration) and the specific types/whatever used to "fill in" the template. For example, if you're trying to use a `Foo<int>`, the compiler must see both the Foo template and the fact that you're trying to make a specific `Foo<int>`.
3. Your compiler probably doesn't remember the details of one .cpp file while it is compiling another .cpp file. It *could*, but most do not and if you are reading this FAQ, it almost definitely does not. BTW this is called the "separate compilation model."

Now based on those facts, here's an example that shows why things are the way they are. Suppose you have a template Foo defined like this:

```C++
template<typename T>
class Foo {
public:
  Foo();
  void someMethod(T x);
private:
  T x;
};
```

Along with similar definitions for the member functions:

```C++
template<typename T>
Foo<T>::Foo() {
  ...
}

template<typename T>
void Foo<T>::someMethod(T x) {
  ...
}
```

Now suppose you have some code in file `Bar.cpp` that uses `Foo<int>`:

```
// Bar.cpp

void blah_blah_blah() {
  ...
  Foo<int> f;
  f.someMethod(5);
  ...
}
```

Clearly somebody somewhere is going to have to use the "pattern" for the constructor definition and for the `someMethod()` definition and instantiate those when `T` is actually `int` . But if you had put the definition of the constructor and `someMethod()` into file `Foo.cpp` , the compiler would see the template code when it compiled `Foo.cpp` and it would see `Foo<int>` when it compiled `Bar.cpp` , but there would never be a time when it saw both the template code and `Foo<int>` . So by rule #2 above, it could never generate the code for `Foo<int>::someMethod()` .

*A note to the experts:* I have obviously made several simplifications above. This was intentional so please don't complain too loudly. If you know the difference between a .cpp file and a compilation unit, the difference between a class template and a template class, and the fact that templates really aren't just glorified macros, then don't complain: this particular question/answer wasn't aimed at you to begin with. I simplified things so newbies would "get it," even if doing so offends some experts.

*Reminder:* Read the [next](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl.html "[35.13] How can I avoid linker errors with my template functions?") [two](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl-export-keyword.html "[35.14] How does the C++ keyword export help with template linker errors?") FAQs for some solutions to this problem.