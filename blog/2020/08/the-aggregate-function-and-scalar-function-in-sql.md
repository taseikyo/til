> @Date    : 2020-08-30 16:11:01
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/zhangxuefan/article/details/6139487) [漠北荒原狼](https://me.csdn.net/zhangxuefan) 2011-01-14 16:51:00

# SQL 中的 aggregate 函数和 scalar 函数

## aggregate 函数

是针对**一系列值**的操作，返回一个单一的值

- AVG() 返回某列的平均值
- COUNT() 返回某列的函数；COUNT(* ) 返回被选行数
- MAX() 返回某列的最大值
- MIN() 返回某列的最小值
- SUM() 返回某列的总和
- FIRST() 返回指定的列中第一个记录的值
- LAST() 返回指定的列中最后一个记录的值


## scalar 函数

是针对**一个单一的值**的操作，返回基于输入值的一个单一值

- UCASE() 将某个域转换为大写
- LCASE() 将某个域转换为小写
- MID(column_name,start[,length]) 用于从文本字段中提取字符
- LEN() 返回某个文本域的长度
- ROUND() 对某个值进行四舍五入
- NOW() 返回当前系统的时间
- FORMAT() 用于对字段的显示进行格式化