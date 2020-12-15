> @Date    : 2020-09-04 10:39:20
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 如何解决模板类编译问题

这两篇文章是之前 [模板类的声明与定义分开的问题](why-can't-i-separate-the-definition-of-my-templates-class-from-its-declaration-and-put-it-inside-a-cpp-file.md) 的后续，那篇文章介绍了为什么分开放置会出错，这两篇文章则提出了解决方案。

- [35.13 How can I avoid linker errors with my template functions?](#3513)
- [35.14 How does the C++ keyword export help with template linker errors?](#3514)

## 35.13

[[35.13] How can I avoid linker errors with my template functions? Updated!](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl.html)

[![](http://www.cs.technion.ac.il/users/yechiel/c++-faq/cpp11-begin.png)](http://www.cs.technion.ac.il/users/yechiel/c++-faq/standardization.html)This answer will be updated due to C++11 extern template. Watch this space for updates in the near future!

Tell your C++ compiler which instantiations to make while it is compiling your template function's .cpp file.

As an example, consider the header file foo.h which contains the following template function declaration:

```C++
// File "foo.h"
template<typename T>
extern void foo();
```

Now suppose file `foo.cpp` actually defines that template function:

```C++
// File "foo.cpp"
#include <iostream>
#include "foo.h"

template<typename T>
void foo() {
  std::cout << "Here I am!\n";
}
```

Suppose file `main.cpp` uses this template function by calling `foo<int>()`:

```C++
// File "main.cpp"
#include "foo.h"

int main() {
  foo<int>();
  ...
}
```

If you compile and (try to) link these two .cpp files, most compilers will generate linker errors. There are **two solutions** for this. The first solution is to physically move the definition of the template function into the .h file, even if it is not an inline function. This solution may (or may not!) cause significant code bloat, meaning your executable size may increase dramatically (or, if your compiler is smart enough, may not; try it and see).

The other solution is to leave the definition of the template function in the .cpp file and simply add the line `template void foo<int>();` to that file:

```C++
// File "foo.cpp"
#include <iostream>
#include "foo.h"

template<typename T> void foo() {
  std::cout << "Here I am!\n";
}

template void foo<int>();
```

If you can't modify `foo.cpp` , simply create a new .cpp file such as `foo-impl.cpp` as follows:

```C++
// File "foo-impl.cpp"
#include "foo.cpp"

template void foo<int>();
```

Notice that `foo-impl.cpp` `#include` a .cpp file, not a .h file. If that's confusing, click your heels twice, think of Kansas, and repeat after me, "I will do it anyway even though it's confusing." You can trust me on this one. But if you don't trust me or are simply curious, [the rationale is given earlier](http://www.cs.technion.ac.il/users/yechiel/c++-faq/templates-defn-vs-decl.html "[35.12] Why can't I separate the definition of my templates class from its declaration and put it inside a .cpp file?").

## 35.14

[[35.14] How does the C++ keyword export help with template linker errors? Updated!](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl-export-keyword.html)

[![](http://www.cs.technion.ac.il/users/yechiel/c++-faq/cpp11-begin.png)](http://www.cs.technion.ac.il/users/yechiel/c++-faq/standardization.html)This answer will be updated due to C++11 extern template. Watch this space for updates in the near future!

The C++ keyword *export* was originally designed to eliminate the need to [include a template definition](http://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-fn-defn-from-decl.html "[35.13] How can I avoid linker errors with my template functions?") (either by providing the definition in the header file or by including the implementation file). However, only a few compilers ever supported this capability, such as [Comeau C++](http://www.comeaucomputing.com/tryitout "www.comeaucomputing.com/tryitout") and [Sun Studio](http://docs.sun.com/source/816-2460/Program_Org.html#pgfId-780 "docs.sun.com/source/816-2460/Program_Org.html"), and the general concensus was that it was not worth the trouble.

Because of that, the C++11 standardization committee has voted to remove the *export* feature from the language. Assuming this meets final approval, *export* will remain a reserved word but it will no longer have any meaning in the standard.

If you are working with a compiler that supports the *export* keyword, it will probably continue to support the keyword via some sort of compiler option or extension until its users migrate away from it. If you already have code that uses *export*, you can use a fairly simple discipline to allow your code to easily migrate if/when your compiler stops supporting it entirely. Just define your template header-files like this:

```C++
// File Foo.h

#ifdef USE_EXPORT_KEYWORD
export
#endif
template<typename T>
class Foo {
  ...
};

#ifndef USE_EXPORT_KEYWORD
  #include "Foo.cpp"
#endif
```

And define your non-inline functions in a source-file like this:

```C++
// File Foo.cpp

#ifdef USE_EXPORT_KEYWORD
export
#endif
template<typename T> ...
```

Then compile with `-DUSE_EXPORT_KEYWORD` , or whatever equivalent compiler option lets you set a preprocessor symbol like `USE_COMPILER_KEYWORD` , and if/when your compiler removes support for *export*, just remove that compiler option.