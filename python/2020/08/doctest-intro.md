> @Date    : 2020-08-15 16:25:00
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# doctest 简介

doctest 是 Python 自带的测试框架库，本篇介绍 doctest 的两种方式：

1. [嵌入到源代码中](#嵌入模式)
2. [做成独立文件](#独立文件模式)

在 doctest 的官网上是这么介绍的：

The [doctest](https://docs.python.org/3/library/doctest.html) module searches for pieces of text that look like interactive Python sessions, and then executes those sessions to verify that they work exactly as shown. There are several common ways to use doctest:

- To check that a module’s docstrings are up-to-date by verifying that all interactive examples still work as documented
- To perform regression testing by verifying that interactive examples from a test file or a test object work as expected
- To write tutorial documentation for a package, liberally illustrated with input-output examples. Depending on whether the examples or the expository text are emphasized, this has the flavor of “literate testing” or “executable documentation”

翻译下就是：doctest 会搜索那些看起来像交互式会话的 Python 代码片段，然后尝试执行并验证结果。

## 嵌入模式

下面是官网给出的一个例子：

```Python
"""
This is the "example" module.

The example module supplies one function, factorial().  For example,

>>> factorial(5)
120
"""


def factorial(n):
    """Return the factorial of n, an exact integer >= 0.

    >>> [factorial(n) for n in range(6)]
    [1, 1, 2, 6, 24, 120]
    >>> factorial(30)
    265252859812191058636308480000000
    >>> factorial(-1)
    Traceback (most recent call last):
        ...
    ValueError: n must be >= 0

    Factorials of floats are OK, but the float must be an exact integer:
    >>> factorial(30.1)
    Traceback (most recent call last):
        ...
    ValueError: n must be exact integer
    >>> factorial(30.0)
    265252859812191058636308480000000

    It must also not be ridiculously large:
    >>> factorial(1e100)
    Traceback (most recent call last):
        ...
    OverflowError: n too large
    """

    import math
    if not n >= 0:
        raise ValueError("n must be >= 0")
    if math.floor(n) != n:
        raise ValueError("n must be exact integer")
    if n+1 == n:  # catch a value like 1e300
        raise OverflowError("n too large")
    result = 1
    factor = 2
    while factor <= n:
        result *= factor
        factor += 1
    return result


if __name__ == "__main__":
    import doctest
    doctest.testmod()
```

运行：

```bash
>> python example.py
```

然后发现没有任何输出 :3，这意味着所有的测试正确，加入 `-v` 选项后 doctest 会输出所有细节：

```bash
>> python example.py -v
Trying:
    factorial(5)
Expecting:
    120
ok
Trying:
    [factorial(n) for n in range(6)]
Expecting:
    [1, 1, 2, 6, 24, 120]
ok
Trying:
    factorial(30)
Expecting:
    265252859812191058636308480000000
ok
Trying:
    factorial(-1)
Expecting:
    Traceback (most recent call last):
        ...
    ValueError: n must be >= 0
ok
Trying:
    factorial(30.1)
Expecting:
    Traceback (most recent call last):
        ...
    ValueError: n must be exact integer
ok
Trying:
    factorial(30.0)
Expecting:
    265252859812191058636308480000000
ok
Trying:
    factorial(1e100)
Expecting:
    Traceback (most recent call last):
        ...
    OverflowError: n too large
ok
2 items passed all tests:
   1 tests in __main__
   6 tests in __main__.factorial
7 tests in 2 items.
7 passed and 0 failed.
Test passed.
```

你也可以直接把 `verbose` 参数设置为 `True`，这样就不用在命令行加入 `-v` 选项了。

```Python
if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True)
```

上面例子演示了 doctest 的第一种使用方式，即把测试用例的位置放在整个模块文件的开头，或者紧接着对象声明语句的下一行。

## 独立文件模式

如果不想（或不能）把测试用例写进源代码里，则还可以使用一个独立的文件来保存测试用例。

将测试用例放入 example.txt 中，其内容如下：

```txt
The ``example`` module
======================

Using ``factorial``
-------------------

This is an example text file in reStructuredText format.  First import
``factorial`` from the ``example`` module:

    >>> from example import factorial

Now use it:

    >>> factorial(6)
    120
```

运行：

```bash
>> python -m doctest -v example.txt
Trying:
    from example import factorial
Expecting nothing
ok
Trying:
    factorial(6)
Expecting:
    120
**********************************************************************
File "example.txt", line 14, in example.txt
Failed example:
    factorial(6)
Expected:
    120
Got:
    720
**********************************************************************
1 items had failures:
   1 of   2 in example.txt
2 tests in 1 items.
1 passed and 1 failed.
***Test Failed*** 1 failures.
```
