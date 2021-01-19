> @Date    : 2021-01-19 10:33:32
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# Python 正则表达式 特殊符号和字符

> 原文：https://www.kingkk.com/2017/12/%E6%AD%A3%E5%88%99%E8%A1%A8%E8%BE%BE%E5%BC%8F%E7%89%B9%E6%AE%8A%E7%AC%A6%E5%8F%B7%E5%92%8C%E5%AD%97%E7%AC%A6  kingkk 2017-12-04

原本是 ipynb 格式，使用 `jupyter nbconvert --to markdown python3-re-expr.ipynb` 转化的，生成的 md 文档有很多多余的回车，太蠢了。

## 择一匹配符号：`|`

```python
import re

# 匹配 bat 或 bet 或 bit
bt = 'bat|bet|bit'
m = re.match(bt, 'bat')
if m: print(m.group())
else: print("None match!")
```

    bat

```python
m = re.match(bt, 'bot')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
m = re.search(bt, 'he bit me')
if m: print(m.group())
else: print("None match!")
```

    bit

## 匹配任意单个字符（包括空格，除了换行符\n)：`.`

tip:若想搜索真正的点号可以通过 `\` 转义

```python
anyend = '.end'
# 匹配任意字符
m = re.match(anyend, 'bend')
if m: print(m.group())
else: print("None match!")
```

    bend

```python
# 不匹配无字符
m = re.match(anyend, 'end')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
# 不匹配换行
m = re.match(anyend, '\nend')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
# 匹配 ' '
m = re.match(anyend, ' end')
if m: print(m.group())
else: print("None match!")
```

     end

## 创建字符集: [ ]

[abc] 匹配 a 或 b 或 c 中任意一个字符

```python
m = re.match('[cr][23][dp][o2]', 'r2d2')
if m: print(m.group())
else: print("None match!")
```

    r2d2

```python
m = re.match('[cr][23][dp][o2]', 'c3eo')
if m: print(m.group())
else: print("None match!")
```

    None match!

## 分组

group() 通常用于显示所有匹配部分，但也可以用于取各个子组 groups() 可以用来获取一个包含所有匹配字符串的元组

```python
m = re.match('(\w\w\w)-(\d\d\d)','abc-123')

m.group()  
# 'abc-123'

# 子组 1 
m.group(1) 
# 'abc'

# 子组 2
m.group(2)
# '123'

# 全部子组，存放与元组中  
m.groups()
# ('abc', '123')
```

    ('abc', '123')

```python
# 不存在子组
m = re.match('ab','ab')
m.group(), m.groups()
```

    ('ab', ())

```python
# 一个子组
m = re.match('(ab)','ab')
m.group(), m.group(1), m.groups()
```

    ('ab', 'ab', ('ab',))

```python
# 两个嵌套子组
m = re.match('(a(b))','ab')

m.group(), m.group(1), m.group(2), m.groups()
```

    ('ab', 'ab', 'b', ('ab', 'b'))

## 匹配起始结尾、边界单词

例：(tips 该操作符多用于 search 而不是 match)

- ^form 匹配以 form 作为起始的字符串
- form$ 匹配以 form 为结尾的字符串
- ^form$ 等价于匹配单个 form 字符串
- \b 匹配边界字符串
- \B 匹配非边界字符串

```python
m = re.search('^is', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    is

```python
m = re.search('is$', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
m = re.search('^dog$', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
m = re.search('^is a dog$', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    is a dog

前后出现空格或者换行时都属于 \b 的边界匹配

```python
# 匹配空格作为边界
m = re.search(r'\bdog', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    dog

```python
# 匹配换行符作为边界
m = re.search(r'\bdog', 'is a\ndog')
if m: print(m.group())
else: print("None match!")
```

    dog

```python
# 匹配失败
m = re.search(r'\bog', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    None match!

```python
# \B 匹配非边界字符串
m = re.search(r'\Bog', 'is a dog')
if m: print(m.group())
else: print("None match!")
```

    og

tips: 使用 r'xxx'的原始字符串避免正则匹配时的转义

## 脱字符 `^`

直接使用表示匹配字符串的起始部分 紧跟在左括号右边表示不匹配给定字符集，例如

- [^\n] 不匹配换行符
- [^aeiou] 不匹配元音字符

```python
re.findall('[^aeiou]', 'abcdefg')
```

    ['b', 'c', 'd', 'f', 'g']

## 拓展符号

(?iLmsux) 用以标记并实现某些功能

这里的”i”, “L”, “m”, “s”, “u”, “x”，它们不匹配任何字串，而是表示对应 python 中 re 模块当中的 (re.I, re.L, re.M, re.S, re.U, re.X) 的 6 种选项。

```
I = IGNORECASE # 忽略大小写
L = LOCALE     # 字符集本地化,为了支持多语言版本的字符集使用环境
U = UNICODE    # 使用\w,\W,\b,\B这些元字符时将按照UNICODE定义的属性
M = MULTILINE  # 多行模式,改变 ^ 和 $ 的行为
S = DOTALL     # '.' 的匹配不受限制,包括换行符
X = VERBOSE    # 冗余模式,可以忽略正则表达式中的空白和#号的注释
```

### re.I/IGNORECASE (忽略大小写的匹配)

```python
re.findall(r'(?i)yes', 'Yes?yes.Yes!!')
```

    ['Yes', 'yes', 'Yes']

```python
re.findall(r'yes', 'Yes?yes.Yes!!', re.I)
```

    ['Yes', 'yes', 'Yes']

```python
re.findall(r'(?i)th\w+', 'The?tHoEs.tHat!!')
```

    ['The', 'tHoEs', 'tHat']

```python
re.findall(r'th\w+', 'The?tHoEs.tHat!!', re.I)
```

    ['The', 'tHoEs', 'tHat']

### re.M/MULTILINE（进行跨行搜索）

```python
# 匹配 th 开头的段落
re.findall(r'(?m)(^th[\w]+)',"""
this is first line,
another line,
that line,it's the best
""")
```

    ['this', 'that']

```python
re.findall(r'(^th[\w]+)',"""
this is first line,
another line,
that line,it's the best
""", re.M)
```

    ['this', 'that']

### re.S/DOTALL (使点号 . 可以用来表示换行符 \n)

```python
# 成功匹配到 \ n
re.findall(r'(?s)(th.+)',"""
this is first line,
another line,
that line,it's the best
""")
```

    ["this is first line,\nanother line,\nthat line,it's the best\n"]

```python
# 成功匹配到 \ n
re.findall(r'(th.+)',"""
this is first line,
another line,
that line,it's the best
""", re.S)
```

    ["this is first line,\nanother line,\nthat line,it's the best\n"]

### re.X/VERBOSE (抑制正则表达式中的空白符，以创建更易读的正则表达式)

tips: 空格符可用 [ ] 等字符类代替，并且可以在正则中通过井号 # 来注释

```python
re.search(r'''(?x) 
\((\d{3})\) #区号
[ ] #空白符
(\d{3}) #前缀
- #横线
(\d{4}) #终点数字''',
'(800) 555-1212').groups()
```

    ('800', '555', '1212')

### `(?:)` 对正则表达式进行分组，但不保存改分组 常用于需要对改分组进行 +* 等操作，但又不需要将改分组提取的情况

使用 (?:) 时，groups 中并未出现 code

```python
m = re.match(r'http://(?:\w+\.)*(\w+\.com)','http://code.google.com')
m.groups()
```

    ('google.com',)

未使用 (?:) 时，groups 中出现 code

```python
m=re.match(r'http://(\w+\.)*(\w+\.com)', 'http://code.google.com')
m.groups()
```

    ('code.', 'google.com')

```python
# 仅提取域名
re.findall(r'http://(?:\w+\.)*(\w+\.com)', 
           'http://google.com http://www.google.com http://code.google.com')
```

    ['google.com', 'google.com', 'google.com']

### (?P=name) 使用自定义表示符，而并非 1 至 N 递增

```python
astr1 = 'AAbb aabb'
astr2 = 'aabb aabb'
astr3 = 'aabb ccbb'
 
for s in astr1,astr2,astr3:
    result = re.match(r'(?i)(?P<pattern>[\w]+) (?P=pattern)',s)
    if result:
        print(f'{s} match result is {result.group()}')
    else:
        print(f'{s} match Nothing')
```

    AAbb aabb match result is AAbb aabb
    aabb aabb match result is aabb aabb
    aabb ccbb match Nothing


从下面例子可以看到 (`?P<pattern>`) 可以用来标记一些模糊的模式，然后在同一个正则表达式中，我们可以通过 (`?P=pattern`) 来复用之前的内容，这就是它们两个的用法区别，一个用于标记，一个用于在同一个正则表达式中复用，特别提醒：同一个正则表达式，这是因为，有些时候我们可能需要在不同的表达式中复用，如下

```python
astr = 'aabb aacc aadd'
result = re.sub(r'(?i)aa(?P<pattern>[\w]+)',r'bb\g<pattern>',astr)
print(f'{astr} has been substituted to {result}')
```

    aabb aacc aadd has been substituted to bbbb bbcc bbdd

可以看到 `\g<name>` 可以用于不同正则表达式的引用！

### (?=) 正向前视匹配断言

所谓的前视，就是往正则匹配方向的前方，我们所谓的后方进行判断。通过添加一些判断条件，使匹配更加精准。 匹配后续内容等于 (?=)  中内容的字符串

```python
#匹配域名为 google.com 的用户名
re.findall(r'\w+(?=@google.com)', '''
host@baidu.com
root@google.com
user@qq.com
admin@google.com
''')
```

    ['root', 'admin']

### (?!) 负向前视断言

匹配后续内容不等于 (?!) 中内容的字符串

```python
# 匹配域名不为 google 的用户名
re.findall(r'(?m)^\w+@(?!google.com)',''' 
host@baidu.com
root@google.com
user@qq.com
admin@google.com
''')
```

    ['host@', 'user@']

## 非贪婪匹配 ?

贪婪匹配：正则表达式通过从左至右，试图尽可能多的获取匹配字符 通过在 * + 后使用 ? 进行非贪婪匹配
