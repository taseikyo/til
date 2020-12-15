> @Date    : 2020-11-24 15:55:21
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# go 的 []rune 和 []byte 区别

> 原文：https://learnku.com/articles/23411/the-difference-between-rune-and-byte-of-go 2018-5-14

> **原文转载** [go 的 [] rune 和 [] byte 区别](https://www.njphper.com/posts/c251fcd3.html)

在看到 go 字符串的时候， 偶然看到 **[]rune(s)**, 它可以将字符串转化成 unicode 码点。那么它和 **[]byte(s)** 有什么区别呢？来测试一下

```Go
first := "fisrt"
fmt.Println([]rune(first))
fmt.Println([]byte(first))
```

> [102 105 115 114 116] // 输出结果 [] rune  
> [102 105 115 114 116] // 输出结果 [] byte

从输出来看， 没有任何区别， 作者不可能无缘无故弄出两个相同的东西，那么到底区别在哪里呢？翻看源码才知道

```Go
// byte is an alias for uint8 and is equivalent to uint8 in all ways. It is
// used, by convention, to distinguish byte values from 8-bit unsigned
// integer values.
type byte = uint8

// rune is an alias for int32 and is equivalent to int32 in all ways. It is
// used, by convention, to distinguish character values from integer values.
type rune = int32
```

原来是 `byte` 表示一个字节，`rune` 表示四个字节，那么就可以得出了结论了，来看一段代码，使用中文字符串

```Go
first := "社区"
fmt.Println([]rune(first))
fmt.Println([]byte(first))
```

> [31038 21306] // 输出结果 [] rune  
> [231 164 190 229 140 186]// 输出结果 [] byte

这里也可以很清晰的看出这里的中文字符串每个占三个字节， 区别也就一目了然了。  
说道这里正好可以提一下 Go 语言切割中文字符串，Go 的字符串截取和切片是一样的 s [n:m] **左闭右开**的原则，看一下例子

```Go
s := "golangcaff"
fmt.Println(s[:3])
```

> gol // 输出，看起来没问题， 顺利截取了三个字符

如果换成中文的呢？来看一下例子

```
s := "截取中文"
//试试这样能不能截取?
fmt.Println(s[:2])
```

> ?? // 输出 在预料之中， 输出了常见的？？

那么该如何截取呢？这里就需要将中文利用 [] rune 转换成 unicode 码点， 再利用 string 转化回去， 来看一下例子。

```Go
s := "截取中文"
//试试这样能不能截取?
res := []rune(s)
fmt.Println(string(res[:2]))
```

> 截取 // 输出，顺利截取了

当然你可以使用 [] byte 来截取， 但是这样你就需要知道你的中文字符到底占几个字节， 似乎这种方法不可取，因为你无法得知。  
为什么 **s[:n]** 无法直接截取呢， 通过实验我猜测如果直接截取的话，底层会将中文转化成 **[]byte**， 而不是 **[]rune**。你可以尝试一下:

```Go
s := "截取中文"
//试试这样能不能截取?
fmt.Println(s[:3])
```

> 截 // 输出

当然这只是我猜测的， 没有看源码具体实现。
