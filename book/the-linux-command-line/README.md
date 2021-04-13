> @Date    : 2021-04-13 17:38:59
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 快乐 Linux 命令行

> 原链接：github.com/billie66/TLCL

精炼了一下内容，把该留下我觉得会用到的东西留下了。

## 7、重定向

1、利用重定向清空一个文件：

```Bash
> foo.txt
```

2、重定向标准输出和错误到同一个文件：

```Bash
ls -l /bin/usr > ls-output.txt 2>&1
ls -l /bin/usr &> ls-output.txt
```

**顺序很重要**

```Bash
2>&1 > ls-output.txt
```

上述命令将标准错误定向到屏幕

3、如果 cat 没有给出任何参数，它会从标准输入读入数据，又因为标准输入默认情况下连接到
键盘，它会等待我们输入数据！

输入 Ctrl-d 来告诉 cat，在标准输入中，它已经到达文件末尾（EOF）


4、tee 程序从标准输入读入数据，并且同时复制数据到标准输出（允
许数据继续随着管道线流动）和一个或多个文件。

```Bash
ls /usr/bin | tee ls.txt | grep zip
bunzip2
bzip2
```

## 8、从 shell 眼中看世界

1、通配符

```Bash
echo *
Desktop Documents ls-output.txt Music Pictures Public Templates Videos
```

为什么 echo 不打印星号呢？原来星号意味着匹配文件名中的任意字符，shell 在 echo 命令被执行前将其展开成了另外的东西（在这里，就是在当前工作目录下的文件名字）

```Bash
echo [[:upper:]]*
Desktop Documents Music Pictures Public Templates Videos
```

这里展开了大写字母开头的所有文件

```Bash
echo ~foo
/home/foo
```

2、算术运算

```Bash
echo $(($((5**2)) * 3))
75
```

原来 shell 也支持幂运算

3、大括号展开

```Bash
echo Number_{1..5}
Number_1
Number_2
Number_3
Number_4
Number_5

echo {Z..A}
Z Y X W V U T S R Q P O N M L K J I H G F E D C B A

echo a{A{1,2},B{3,4}}b
aA1b aA2b aB3b aB4b

mkdir {2007..2009}-0{1..9} {2007..2009}-{10..12}
ls
2007-01 2007-07 2008-01 2008-07 2009-01 2009-07
2007-02 2007-08 2008-02 2008-08 2009-02 2009-08
2007-03 2007-09 2008-03 2008-09 2009-03 2009-09
2007-04 2007-10 2008-04 2008-10 2009-04 2009-10
2007-05 2007-11 2008-05 2008-11 2009-05 2009-11
2007-06 2007-12 2008-06 2008-12 2009-06 2009-12
```

太强了，学到了！

4、命令替换

```Bash
ls -l $(which cp)
-rwxr-xr-x 1 root root 71516 2007-12-05 08:58 /bin/cp
```

可以在不知道 cp 命令完整路径名的情况下得到它的文件属性列表

```Bash
file $(ls /usr/bin/* | grep zip)
/usr/bin/bunzip2:
symbolic link to `bzip2'
```

旧版的命令替换是用 "\`"

6、单词分割

```Bash
echo this is a      test
this is a test
```

shell 利用单词分割删除掉 echo 命令的参数列表中多余的空格

5、双引号引用

如果把文本放在双引号中，shell 使用的特殊字符，都失去它们的特殊含义，被当作普通字符来看待，除了下面几个特殊字符：

```Bash
$ ` \
```

这意味着单词分割、路径名展开（`ls D*`）、波浪线展开（`cd ~foo`）和花括号展开（`echo Number_{1..5}`）都将失效

但是参数展开、算术展开和命令替换仍然执行：

```Bash
echo "$USER $((2+2)) $(cal)"
me 4
February 2008
Su Mo Tu We Th Fr Sa
...
```

单词分割机制会在单词中寻找空格，制表符，和换行符，并把它们看作单词之间的界定符，这意味着无引用的空格，制表符和换行符都不是文本的一部分，它们只作为分隔符使用

一旦加上双引号，我们的命令行就包含一个带有一个参数的命令

```Bash
echo "this is a    test"
this is a    test
```

单词分割机制把换行符看作界定符，对命令替换产生了一个虽然微妙但有趣的影响：

```Bash
tian@me ~> echo $(cal)
April 2021 Su Mo Tu We Th Fr Sa 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
tian@me ~> echo "$(cal)"
     April 2021       
Su Mo Tu We Th Fr Sa  
             1  2  3  
 4  5  6  7  8  9 10  
11 12 13 14 15 16 17  
18 19 20 21 22 23 24  
25 26 27 28 29 30
```

在第一个实例中，没有引用的命令替换导致命令行包含 38 个参数。在第二个例子中，命令行只有一个参数，参数中包括嵌入的空格和换行符

6、单引号

如果需要禁止所有的展开，我们要使用单引号

无引用，双引号，和单引号的比较：

```Bash
[me@linuxbox ~]$ echo text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER
text /home/me/ls-output.txt a b foo 4 me
[me@linuxbox ~]$ echo "text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER"
text ~/*.txt {a,b} foo 4 me
[me@linuxbox ~]$ echo 'text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER'
text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER
```

随着引用程度加强，越来越多的展开被禁止

## 9、键盘高级操作技巧

1、历史命令展开

通过使用 "! 字符，shell 为历史列表中的命令，提供了一个特殊的展开类型

|   序列   |                               行为                          |
|:--------:|:-----------------------------------------------------------|
|    !!    | 重复最后一次执行的命令。可能按下上箭头按键和 enter 键更容易些。 |
|  !number |                重复历史列表中第 number 行的命令。            |
|  !string |           重复最近历史列表中，以这个字符串开头的命令。        |
| !?string |            重复最近历史列表中，包含这个字符串的命令。         |


```Bash
!88
```

bash 会把 "!88" 展开成为历史列表中 88 行的内容

## 10、权限

1、文件属性

| 属性 | 文件 | 目录 |
|:-:|:-|:-|
| r | 允许打开并读取文件内容。 | 允许列出目录中的内容，前提是目录必须设置了可执行属性（x）。 |
| w | 允许写入文件内容或截断文件。但是不允许对文件进行重命名或删除，重命名或删除是由目录的属性决定的。 | 允许在目录下新建、删除或重命名文件，前提是目录必须设置了可执行属性（x）。 |
| x | 允许将文件作为程序来执行，使用脚本语言编写的程序必须设置为可读才能被执行。 | 允许进入目录，例如：`cd directory`|

2、切换用户

`su [-[l]] [user]`

如果包含 "-l" 选项，那么会为指定用户启动一个需要登录的 shell。这意味着会加载此用户的 shell 环境，并且工作目录会更改到这个用户的家目录。

`su -c 'command'`

使用这种模式，命令传递到一个新 shell 中执行。把命令用单引号引起来很重要，因为我们不想命令在我们的 shell 中展开，但需要在新 shell 中展开。

27、自顶向下设计

1、局部变量

```Bash
#!/bin/bash
# local-vars.sh: script to demonstrate local variables
foo=0 # global variable foo
funct_1 () {
	local foo
	# variable foo local to funct_1
	foo=1
	echo "funct_1: foo = $foo"
}
funct_2 () {
	local foo
	# variable foo local to funct_2
	foo=2
	echo "funct_2: foo = $foo"
}
echo "global:
foo = $foo"
funct_1
echo "global: foo = $foo"
funct_2
echo "global: foo = $foo"
```

```Bash
local-vars.sh
global:
foo = 0
funct_1: foo = 1
global:
foo = 0
funct_2: foo = 2
global:
foo = 0
```

## 29、读取键盘输入

1、read 从标准输入读取数值

`read [-options] [variable...]`

这里的 options 是下面列出的可用选项中的一个或多个，且 variable 是用来存储输入数值的一个或多个变量名。如果没有提供变量名，shell 变量 REPLY 会包含数据行。

## 30、流程控制：case 分支

```Bash
case word in
	[pattern [| pattern]...) commands ;;]...
esac
```

```Bash
#!/bin/bash
# read-menu: a menu driven system information program
clear
echo "
Please Select:
1. Display System Information
2. Display Disk Space
3. Display Home Space Utilization
0. Quit
"
read -p "Enter selection [0-3] > "
if [[ $REPLY =~ ^[0-3]$ ]]; then
	if [[ $REPLY == 0 ]]; then
		echo "Program terminated."
		exit
	fi
	if [[ $REPLY == 1 ]]; then
		echo "Hostname: $HOSTNAME"
		uptime
		exit
	fi
	if [[ $REPLY == 2 ]]; then
		df -h
		exit
	fi
	if [[ $REPLY == 3 ]]; then
		if [[ $(id -u) -eq 0 ]]; then
			echo "Home Space Utilization (All Users)"
			du -sh /home/*
		else
			echo "Home Space Utilization ($USER)"
			du -sh $HOME
		fi
		exit
	fi
else
	echo "Invalid entry." >&2
	exit 1
fi
```

```Bash
#!/bin/bash
# case-menu: a menu driven system information program
clear
echo "
Please Select:
1. Display System Information
2. Display Disk Space
3. Display Home Space Utilization
0. Quit
"
read -p "Enter selection [0-3] > "
case $REPLY in
	0) echo "Program terminated."
		exit
		;;
	1) echo "Hostname: $HOSTNAME"
		uptime
		;;
	2) df -h
		;;
	3) if [[ $(id -u) -eq 0 ]]; then
			echo "Home Space Utilization (All Users)"
			du -sh /home/*
		else
			echo "Home Space Utilization ($USER)"
			du -sh $HOME
		fi
		;;
	*) echo "Invalid entry" >&2
		exit 1
		;;
esac
```


## 34、for 循环

1、传统格式

```Bash
for variable [in words]; do
	commands
done
```

2、C 语言格式

```Bash
for (( expression1; expression2; expression3 )); do
	commands
done
```

## 37、奇珍异宝

1、组命令和子 shell

```Bash
# 组命令
{ command1; command2; [command3; ...] }
# 子 shell
(command1; command2; [command3;...])
```

2、异步执行

```Bash
#!/bin/bash
# async-parent : Asynchronous execution demo (parent)
echo "Parent: starting..."
echo "Parent: launching child script..."
async-child &
pid=$!
echo "Parent: child (PID= $pid) launched."
echo "Parent: continuing..."
sleep 2
echo "Parent: pausing to wait for child to finish..."
wait $pid
echo "Parent: child is finished. Continuing..."
echo "Parent: parent is done. Exiting."
```

```Bash
#!/bin/bash
# async-child : Asynchronous execution demo (child)
echo "Child: child is running..."
sleep 5
echo "Child: child is done. Exiting."
```

```Bash
[me@linuxbox ~]$ async-parent
Parent: starting...
Parent: launching child script...
Parent: child (PID= 6741) launched.
Parent: continuing...
Child: child is running...
Parent: pausing to wait for child to finish...
Child: child is done. Exiting.
Parent: child is finished. Continuing...
Parent: parent is done. Exiting.
```
