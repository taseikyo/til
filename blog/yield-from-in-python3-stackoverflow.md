> @Date    : 2020-11-12 10:48:05
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# In practice, what are the main uses for the new “yield from” syntax in Python 3.3?

> 原文：https://stackoverflow.com/a/26109157/7669794

Let's get one thing out of the way first. The explanation that `yield from g` is equivalent to `for v in g: yield v` **does not even begin to do justice** to what `yield from` is all about. Because, let's face it, if all `yield from` does is expand the `for` loop, then it does not warrant adding `yield from` to the language and preclude a whole bunch of new features from being implemented in Python 2.x.

What `yield from` does is it **_establishes a transparent bidirectional connection between the caller and the sub-generator_**:

- The connection is "transparent" in the sense that it will propagate everything correctly too, not just the elements being generated (e.g. exceptions are propagated).
    
- The connection is "bidirectional" in the sense that data can be both sent _from_ and _to_ a generator.
    

(_If we were talking about TCP, `yield from g` might mean "now temporarily disconnect my client's socket and reconnect it to this other server socket"._)

BTW, if you are not sure what _sending data to a generator_ even means, you need to drop everything and read about _coroutines_ first—they're very useful (contrast them with _subroutines_), but unfortunately lesser-known in Python. [Dave Beazley's Curious Course on Coroutines](http://dabeaz.com/coroutines/) is an excellent start. [Read slides 24-33](http://dabeaz.com/coroutines/Coroutines.pdf) for a quick primer.

## Reading data from a generator using yield from

```Python
def reader():
    """A generator that fakes a read from a file, socket, etc."""
    for i in range(4):
        yield '<< %s' % i

def reader_wrapper(g):
    # Manually iterate over data produced by reader
    for v in g:
        yield v

wrap = reader_wrapper(reader())
for i in wrap:
    print(i)

# Result
<< 0
<< 1
<< 2
<< 3
```

Instead of manually iterating over `reader()`, we can just `yield from` it.

```Python
def reader_wrapper(g):
    yield from g
```

That works, and we eliminated one line of code. And probably the intent is a little bit clearer (or not). But nothing life changing.

## Sending data to a generator (coroutine) using yield from - Part 1

Now let's do something more interesting. Let's create a coroutine called `writer` that accepts data sent to it and writes to a socket, fd, etc.

```Python
def writer():
    """A coroutine that writes data *sent* to it to fd, socket, etc."""
    while True:
        w = (yield)
        print('>> ', w)
```

Now the question is, how should the wrapper function handle sending data to the writer, so that any data that is sent to the wrapper is _transparently_ sent to the `writer()`?

```Python
def writer_wrapper(coro):
    # TBD
    pass

w = writer()
wrap = writer_wrapper(w)
wrap.send(None)  # "prime" the coroutine
for i in range(4):
    wrap.send(i)

# Expected result
>>  0
>>  1
>>  2
>>  3
```

The wrapper needs to _accept_ the data that is sent to it (obviously) and should also handle the `StopIteration` when the for loop is exhausted. Evidently just doing `for x in coro: yield x` won't do. Here is a version that works.

```Python
def writer_wrapper(coro):
    coro.send(None)  # prime the coro
    while True:
        try:
            x = (yield)  # Capture the value that's sent
            coro.send(x)  # and pass it to the writer
        except StopIteration:
            pass
```

Or, we could do this.

```Python
def writer_wrapper(coro):
    yield from coro
```

That saves 6 lines of code, make it much much more readable and it just works. Magic!

## Sending data to a generator yield from - Part 2 - Exception handling

Let's make it more complicated. What if our writer needs to handle exceptions? Let's say the `writer` handles a `SpamException` and it prints `***` if it encounters one.

```Python
class SpamException(Exception):
    pass

def writer():
    while True:
        try:
            w = (yield)
        except SpamException:
            print('***')
        else:
            print('>> ', w)
```

What if we don't change `writer_wrapper`? Does it work? Let's try

```Python
# writer_wrapper same as above

w = writer()
wrap = writer_wrapper(w)
wrap.send(None)  # "prime" the coroutine
for i in [0, 1, 2, 'spam', 4]:
    if i == 'spam':
        wrap.throw(SpamException)
    else:
        wrap.send(i)

# Expected Result
>>  0
>>  1
>>  2
***
>>  4

# Actual Result
>>  0
>>  1
>>  2
Traceback (most recent call last):
  ... redacted ...
  File ... in writer_wrapper
    x = (yield)
__main__.SpamException
```

Um, it's not working because `x = (yield)` just raises the exception and everything comes to a crashing halt. Let's make it work, but manually handling exceptions and sending them or throwing them into the sub-generator (`writer`)

```Python
def writer_wrapper(coro):
    """Works. Manually catches exceptions and throws them"""
    coro.send(None)  # prime the coro
    while True:
        try:
            try:
                x = (yield)
            except Exception as e:   # This catches the SpamException
                coro.throw(e)
            else:
                coro.send(x)
        except StopIteration:
            pass
```

This works.

```Python
# Result
>>  0
>>  1
>>  2
***
>>  4
```

But so does this!

```Python
def writer_wrapper(coro):
    yield from coro
```

The `yield from` transparently handles sending the values or throwing values into the sub-generator.

This still does not cover all the corner cases though. What happens if the outer generator is closed? What about the case when the sub-generator returns a value (yes, in Python 3.3+, generators can return values), how should the return value be propagated? [That `yield from` transparently handles all the corner cases is really impressive](https://www.python.org/dev/peps/pep-0380/#formal-semantics). `yield from` just magically works and handles all those cases.

I personally feel `yield from` is a poor keyword choice because it does not make the _two-way_ nature apparent. There were other keywords proposed (like `delegate` but were rejected because adding a new keyword to the language is much more difficult than combining existing ones.

In summary, it's best to think of `yield from` as a **`transparent two way channel`** between the caller and the sub-generator.

References:

1. [PEP 380](http://www.python.org/dev/peps/pep-0380/) - Syntax for delegating to a sub-generator (Ewing) [v3.3, 2009-02-13]
2. [PEP 342](http://www.python.org/dev/peps/pep-0342/) - Coroutines via Enhanced Generators (GvR, Eby) [v2.5, 2005-05-10]