> @Date    : 2021-05-02 14:16:32
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Golang 中 defer 的使用规则

> 原文：https://www.cnblogs.com/vikings-blog/p/7099023.html 2017-06-30 15:24  [vikings blog](https://home.cnblogs.com/u/vikings-blog)

## Table of Contents

- [规则一 当 defer 被声明时，其参数就会被实时解析](#规则一-当-defer-被声明时其参数就会被实时解析)
- [规则二 defer 执行顺序为先进后出](#规则二-defer-执行顺序为先进后出)
- [规则三 defer 可以读取有名返回值](#规则三-defer-可以读取有名返回值)

在 golang 当中，defer 代码块会在函数调用链表中增加一个函数调用。这个函数调用不是普通的函数调用，而是会在函数正常返回，也就是 return 之后添加一个函数调用。因此，defer 通常用来释放函数内部变量。

为了更好的学习 defer 的行为，我们首先来看下面一段代码:

```golang
func CopyFile(dstName, srcName string) (written int64, err error) {
    src, err := os.Open(srcName)
    if err != nil {
        return
    }

    dst, err := os.Create(dstName)
    if err != nil {
        return
    }

    written, err = io.Copy(dst, src)
    dst.Close()
    src.Close()
    return
}
```

这段代码可以运行，但存在'安全隐患'。如果调用 `dst, err := os.Create(dstName)` 失败，则函数会执行 return 退出运行。但之前创建的 src（文件句柄）没有被释放。 上面这段代码很简单，所以我们可以一眼看出存在文件未被释放的问题。 如果我们的逻辑复杂或者代码调用过多时，这样的错误未必会被及时发现。 而使用 defer 则可以避免这种情况的发生，下面是使用 defer 的代码:

```golang
func CopyFile(dstName, srcName string) (written int64, err error) {
    src, err := os.Open(srcName)
    if err != nil {
        return
    }
    defer src.Close()

    dst, err := os.Create(dstName)
    if err != nil {
        return
    }
    defer dst.Close()

    return io.Copy(dst, src)
}
```

通过 defer，我们可以在代码中优雅的关闭 / 清理代码中所使用的变量。defer 作为 golang 清理变量的特性，有其独有且明确的行为。以下是 defer 三条使用规则。

### 规则一 当 defer 被声明时，其参数就会被实时解析

我们通过以下代码来解释这条规则:

```golang
func a() {
    i := 0
    defer fmt.Println(i)
    i++
    return
}
```

上面我们说过，defer 函数会在 return 之后被调用。那么这段函数执行完之后，是不用应该输出 1 呢？

读者自行编译看一下，结果输出的是 0。why？

这是因为虽然我们在 defer 后面定义的是一个带变量的函数: `fmt.Println(i)`。但这个变量 (i) 在 defer 被声明的时候，就已经确定其确定的值了。 换言之，上面的代码等同于下面的代码：

```golang
func a() {
    i := 0
    // i=0，此时就明确告诉 go 在程序退出时，执行输出0的操作
    defer fmt.Println(0)
    i++
    return
}
```

为了更为明确的说明这个问题，我们继续定义一个 defer:

```golang
func a() {
    i := 0
    defer fmt.Println(i) // 输出 0， i 此时就是 0
    i++
    defer fmt.Println(i) // 输出 1，i 此时就是 1
    return
}
```

通过运行结果，可以看到 defer 输出的值，就是定义时的值。**而不是 defer 真正执行时的变量值（很重要，搞不清楚的话就会产生于预期不一致的结果）**

但为什么是先输出 1，在输出 0 呢？ 看下面的规则二。

### 规则二 defer 执行顺序为先进后出

当同时定义了多个 defer 代码块时，golang 安装 **先定义后执行** 的顺序依次调用 defer。不要为什么，golang 就是这么定义的。我们用下面的代码加深记忆和理解:

```golang
func b() {
    for i := 0; i < 4; i++ {
        defer fmt.Print(i)
    }
}
```

在循环中，依次定义了四个 defer 代码块。结合规则一，我们可以明确得知每个 defer 代码块应该输出什么值。 安装先进后出的原则，我们可以看到依次输出了 3210.

### 规则三 defer 可以读取有名返回值

先看下面的代码:

```golang
func c() (i int) {
    defer func() { i++;fmt.Println(i) }()
    return 1
}
```

输出结果是 2。在开头的时候，我们说过 defer 是在 return 调用之后才执行的。 这里需要明确的是 defer 代码块的作用域仍然在函数之内，结合上面的函数也就是说，defer 的作用域仍然在 c 函数之内。因此 defer 仍然可以读取 c 函数内的变量（如果无法读取函数内变量，那又如何进行变量清除呢）。

当执行 return 1 之后，i 的值就是 1。此时此刻，defer 代码块开始执行，对 i 进行自增操作。 因此输出 2.

掌握了 defer 以上三条使用规则，那么当我们遇到 defer 代码块时，就可以明确得知 defer 的预期结果。
