> @Date    : 2020-08-26 16:18:27
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [blog.csdn.net](https://blog.csdn.net/u010520146/article/details/81161762)

在项目中, SQL 的调优对项目的性能来讲至关重要, 所有掌握常见的 SQL 调优方式是必不可少的, 下面介绍几种常见的 SQL 的调优方式, 供借鉴.

## 一. 创建索引

1. 要尽量避免全表扫描，首先应考虑在 where 及 order by 涉及的列上建立索引  
2. (1) 在经常需要进行检索的字段上创建索引，比如要按照表字段 username 进行检索，那么就应该在姓名字段上创建索引，如果经常要按照员工部门和员工岗位级别进行检索，那么就应该在员工部门和员工岗位级别这两个字段上创建索引。  
(2) 创建索引给检索带来的性能提升往往是巨大的，因此在发现检索速度过慢的时候应该首先想到的就是创建索引。  
(3) 一个表的索引数最好不要超过 6 个，若太多则应考虑一些不常使用到的列上建的索引是否有 必要。索引并不是越多越好，索引固然可以提高相应的 select 的效率，但同时也降低了 insert 及 update 的效率，因为 insert 或 update 时有可能会重建索引，所以怎样建索引需要慎重考虑，视具体情况而定。

## 二. 避免在索引上使用计算

在 where 字句中，如果索引列是计算或者函数的一部分，DBMS 的优化器将不会使用索引而使用全表查询, 函数属于计算的一种, 同时在 in 和 exists 中通常情况下使用 EXISTS，因为 in 不走索引

效率低：

```sql
select * from user where salary*22>11000 (salary是索引列)
```

效率高：

```sql
select * from user where salary>11000/22 (salary是索引列)
```

## 三. 使用预编译查询

程序中通常是根据用户的输入来动态执行 SQL，这时应该尽量使用参数化 SQL, 这样不仅可以避免 SQL 注入漏洞攻击，最重要数据库会对这些参数化 SQL 进行预编译，这样第一次执行的时候 DBMS 会为这个 SQL 语句进行查询优化并且执行预编译，这样以后再执行这个 SQL 的时候就直接使用预编译的结果，这样可以大大提高执行的速度。

## 四. 调整 Where 字句中的连接顺序

DBMS 一般采用自下而上的顺序解析 where 字句，根据这个原理表连接最好写在其他 where 条件之前，那些可以过滤掉最大数量记录。

## 五. 尽量将多条 SQL 语句压缩到一句 SQL 中

每次执行 SQL 的时候都要建立网络连接、进行权限校验、进行 SQL 语句的查询优化、发送执行结果，这个过程是非常耗时的，因此应该尽量避免过多的执行 SQL 语句，能够压缩到一句 SQL 执行的语句就不要用多条来执行。

## 六. 用 where 字句替换 HAVING 字句

避免使用 HAVING 字句，因为 HAVING 只会在检索出所有记录之后才对结果集进行过滤，而 where 则是在聚合前刷选记录，如果能通过 where 字句限制记录的数目，那就能减少这方面的开销。HAVING 中的条件一般用于聚合函数的过滤，除此之外，应该将条件写在 where 字句中。

## 七. 使用表的别名

当在 SQL 语句中连接多个表时，请使用表的别名并把别名前缀于每个列名上。这样就可以减少解析的时间并减少哪些友列名歧义引起的语法错误。

## 八. 用 union all 替换 union

当 SQL 语句需要 union 两个查询结果集合时，即使检索结果中不会有重复的记录，如果使用 union 这两个结果集同样会尝试进行合并，然后在输出最终结果前进行排序，因此如果可以判断检索结果中不会有重复的记录时候，应该用 union all，这样效率就会因此得到提高。

## 九. 考虑使用 “临时表” 暂存中间结果

简化 SQL 语句的重要方法就是采用临时表暂存中间结果，但是，临时表的好处远远不止这些，将临时结果暂存在临时表，后面的查询就在 tempdb 中了，这可以避免程序中多次扫描主表，也大大减少了程序执行中 “共享锁” 阻塞“更新锁”，减少了阻塞，提高了并发性能。但是也得避免频繁创建和删除临时表，以减少系统表资源的消耗。

## 十. 只在必要的情况下才使用事务 begin translation

SQL Server 中一句 SQL 语句默认就是一个事务，在该语句执行完成后也是默认 commit 的。其实，这就是 begin tran 的一个最小化的形式，好比在每句语句开头隐含了一个 begin tran，结束时隐含了一个 commit。

有些情况下，我们需要显式声明 begin tran，比如做 “插、删、改” 操作需要同时修改几个表，要求要么几个表都修改成功，要么都不成功。begin tran 可以起到这样的作用，它可以把若干 SQL 语句套在一起执行，最后再一起 commit。 好处是保证了数据的一致性，但任何事情都不是完美无缺的。Begin tran 付出的代价是在提交之前，所有 SQL 语句锁住的资源都不能释放，直到 commit 掉。  

可见，如果 Begin tran 套住的 SQL 语句太多，那数据库的性能就糟糕了。在该大事务提交之前，必然会阻塞别的语句，造成 block 很多。Begin tran 使用的原则是，在保证数据一致性的前提下，begin tran 套住的 SQL 语句越少越好！有些情况下可以采用触发器同步数据，不一定要用 begin tran。

## 十一. 尽量避免使用游标

尽量避免向客户端返回大数据量，若数据量过大，应该考虑相应需求是否合理。因为游标的效率较差，如果游标操作的数据超过 1 万行，那么就应该考虑改写。

## 十二. 用 varchar/nvarchar 代替 char/nchar

尽可能的使用 varchar/nvarchar 代替 char/nchar ，因为首先变长字段存储空间小，可以节省存储空间，其次对于查询来说，在一个相对较小的字段内搜索效率显然要高些。不要以为 NULL 不需要空间，比如：char(100) 型，在字段建立时，空间就固定了， 不管是否插入值（NULL 也包含在内），都是占用 100 个字符的空间的，如果是 varchar 这样的变长字段， null 不占用空间。

## 十三. 查询 select 语句优化

1. 任何地方都不要使用 select * from t ，用具体的字段列表代替 “*”，不要返回用不到的任何字段  
2. 应尽量避免在 where 子句中对字段进行 null 值判断，否则将导致引擎放弃使用索引而进行全表扫描

如：

```sql
select id from t where num is null
```

可以在 num 上设置默认值 0，确保表中 num 列没有 null 值，

然后这样查询：

```sql
select id from t where num=0
select id from t where num=10 or num=20
```

可以这样查询：

```sql
select id from t where num=10
union all
select id from t where num=20
```

不能前置百分

```sql
select id from t where name like ‘%abc%’
```

若要提高效率，可以考虑全文检索。

```sql
select id from t where num in(1,2,3)
```

对于连续的数值，能用 between 就不要用 in 了：

```sql
select id from t where num between 1 and 3
```

如果查询的两个表大小相当，那么用 in 和 exists 差别不大。  

in：

例如：表 A（小表），表 B（大表）

```sql
select * from A where cc in (select cc from B) 效率低，用到了A表上cc列的索引；     
select * from A where exists(select cc from B where cc=A.cc)   效率高，用到了B表上cc列的索引。
```

相反的

```sql
select * from B where cc in (select cc from A)  效率高，用到了B表上cc列的索引；
select * from B where exists(select cc from A where cc=B.cc)  效率低，用到了A表上cc列的索引。
```

## 十四. 更新 Update 语句优化

如果只更改 1、2 个字段，不要 Update 全部字段，否则频繁调用会引起明显的性能消耗，同时带来大量日志

## 十五. 删除 Delete 语句优化语句

最高效的删除重复记录方法 (因为使用了 ROWID) 例子：

```sql
DELETE FROM EMP E WHERE E.ROWID > (SELECT MIN(X.ROWID) FROM EMP X WHERE X.EMP_NO = E.EMP_NO);
```

## 十六. 插入 Insert 语句优化

在新建临时表时，如果一次性插入数据量很大，那么可以使用 select into 代替 create table，避免造成大量 log ，以提高速度；如果数据量不大，为了缓和系统表的资源，应先 create table，然后 insert。