> @Date    : 2020-11-06 10:35:54
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# URL in C

> 原文：https://susam.in/blog/url-in-c/

By **Susam Pal** on 03 Jun 2011

Here is an interesting C puzzle I created recently. It is a silly one but you might find it amusing.

```C
#include <stdio.h>

int main()
{
    https://susam.in/
    printf("hello, world\n");
    return 0;
}
```

This code compiles and runs successfully.

```Bash
$ c99 hello.c && ./a.out
hello, world
```

However, the [C99 standard](http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf) does not mention anywhere that a URL is a valid syntactic element in C. How does this code work then?

*Update on 04 Jun 2011: The puzzle has been solved in the [comments](https://susam.in/blog/url-in-c/comments/) section. If you want to think about the problem before you see the solutions, this is a good time to pause and think about it. There are spoilers ahead.*

The code works fine because `https:` is a label and `//` following it begins a comment. In case, you are wondering if `//` is indeed a valid comment in C, yes, it is, since C99. Download the [C99 standard](http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf), go to section 6.4.9 (Comments) and read the second point which mentions this:

> Except within a character constant, a string literal, or a comment, the characters `//` introduce a comment that includes all multibyte characters up to, but not including, the next new-line character. The contents of such a comment are examined only to identify multibyte characters and to find the terminating new-line character.

### More ...

If you liked this post, you might also like these:

- [Sequence Points in C](https://susam.in/blog/sequence-points/)
- [Stack Overwriting Function in C](https://susam.in/blog/stack-overwriting-function/)
- [Writing Boot Sector Code in ASM](https://susam.in/blog/writing-boot-sector-code/)
- [Map Caps Lock to Escape](https://github.com/susam/uncap)
