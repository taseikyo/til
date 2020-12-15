> @Date    : 2020-10-15 16:42:35
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

node10 的 root 密码不知道被谁改了，于是找到这篇文章，一句话解决问题，`sudo passwd root` 前提你得有 sudo 权限。第二个方法，如下所示，比较有趣，也需要 sudo 权限，通过编辑 `/etc/shadow` 找回。

```Bash
sudo vim /etc/shadow
# 将 root 的加密密码换成下面这段，然后 root 的密码就被重置为 apple
# $6$LyVpT/aetS$mTDFTG9SzM7iVdP7Kqz6q2lsvgqjA45qXDAEcIUV/eEAaOGreCbd1XMet8itx7z1XM1ZFCb3UUd3toBozQiuZ.
su
# apple
```

# Linux 忘记 root 密码怎么办？

> 原文：https://zhuanlan.zhihu.com/p/35147209 作者：[DeepWeaver](https://www.zhihu.com/people/DeepWeaver) 2018-3-31

## Table of Contents

- [什么是加密函数？](#什么是加密函数)
- [什么是 salt？](#什么是-salt)
- [如何修改密码？](#如何修改密码)

昨天，有个妹子问了我一个问题，她忘记了自己 centos 的 root 密码，问我应该怎么办。我想也没想就答道：准备好重装系统吧！

时间仿佛回到了一年前，我照着 linux 书倒腾新安装的 ubuntu 系统，在 / etc/sudoers 文件中徘徊时突发奇想，如果我把里边我的 sudoer 权限去除，系统会不会阻止我这样做。真是好奇心害死猫，三天后我重装了系统。不小心革掉了自己的命。所以说，linux 系统认为用户知道自己在做什么，把所有的权力都给了用户自己。总之，在探索 linux 系统的过程中，我重装了系统不下 5 次。。。

> linux 账户保存在 / etc/passwd，密码保存在 / etc/shadow 文件中。前者无需超级用户权限即可阅读。

```Bash
➜　ll /etc/passwd /etc/shadow
-rw-r--r-- 1 root root   2.6K 3月   9 11:26 /etc/passwd
-rw-r----- 1 root shadow 1.6K 3月  31 10:42 /etc/shadow
```

> 通过`man 5 passwd`，`man 5 shadow`可查看文件中各字段含义。

但是，一年以后，当再次被问起这个问题时，我又思考了一下。如果你只有 root 用户，而忘记了密码，那没办法，即使暴力破解或者字典破解，由于你不知道加密算法中使用的 salt，是破解不了的。

但是如果你的某个用户拥有 sudoer 权限的话，即使忘了 root 密码，也还是可以修改的。可能你并不了解这里面的加密算法以及 salt 是什么，别急，接下来我把背景知识补充一下。

## 什么是加密函数？

> 密码的散列存储  
> 如果你用过 ss 科学上网，你可能听说过一下这些中的某一个：

```
1. none
2. rc4
3. rc4-md5
4. rc4-md5-6
5. aes-128-ctr
6. aes-192-ctr
7. aes-256-ctr
8. aes-128-cfb
9. aes-192-cfb
10. aes-256-cfb
11. aes-128-cfb8
12. aes-192-cfb8
13. aes-256-cfb8
14. salsa20
15. chacha20
16. chacha20-ietf
```

> [AES,SHA1,DES,RSA,MD5 区别 - CSDN 博客](https://link.zhihu.com/?target=https%3A//blog.csdn.net/hengshujiyi/article/details/45972533) 这里有一篇文章专门讲这些加密方式的区别

总而言之，如果你的密码以明文的方式直接存储在数据库中是很危险的。于是我们想了一种办法，对密码进行 SHA512 加密，所谓加密，你可以理解为一个函数，确切的说是一个不可逆的散列函数（哈希函数），当你把密码当做这个函数的输入，会输出一串加密过的密码，如果你的机器被黑客黑了，他最多只能得到你加密过的密码。同样，每次你输入密码，系统会把密码输入哈希函数，拿输出的值与数据库中的值比较，如果你们有相同的输出，则你们是同一个人，如果函数的输出不同，你们就不是一个人。

比如：

```Bash
mkpasswd -m sha-512
Password: ａｐｐｌｅ
$6$LyVpT/aetS$mTDFTG9SzM7iVdP7Kqz6q2lsvgqjA45qXDAEcIUV/eEAaOGreCbd1XMet8itx7z1XM1ZFCb3UUd3toBozQiuZ.
```

> 在 ubuntu 系统中使用`sudo apt-get install whois`可以获得这个`mkpasswd`命令，通过这个命令我们可以对密码进行加密。

我们看到，如果你的密码是`apple`，密码的散列值貌似是这么一长串。实际上，这一长串密码被 "$" 分割，第一个阿拉伯数字，代表了加密方法的种类， 这里 6 就代表了 sha-512 这种加密方式。第二个我们一会再说。第三个即为`apple`的散列值。系统中不存储`apple`这个密码，存储的是下面的散列值。当你再次输入密码的时候，会再次生成散列值，用于和数据库中的进行比较。

## 什么是 salt？

举个例子，比如，如果你的密码仅仅是一个单词，黑客有一本字典，这个字典的每个单词后面都对应了这个单词的散列值。然后黑客看着你经过加密的密码，一页一页翻看字典。没翻几页他就发现，单词`apple`的散列值咋和你加密过的密码一样？

> 加 Salt 可以一定程度上解决这一问题。所谓加 Salt，就是加点 “佐料”。其基本想法是这样的——当用户首次提供密码时（通常是注册时），由系统自动往这个密码里撒一些 “佐料”，然后再散列。而当用户登录时，系统为用户提供的代码撒上同样的 “佐料”，然后散列，再比较散列值，已确定密码是否正确。

我们刚才看到的`$6$LyVpT/aetS$mTDFTG9SzM7iVdP7Kqz6q2lsvgqjA45qXDAEcIUV/eEAaOGreCbd1XMet8itx7z1XM1ZFCb3UUd3toBozQiuZ.`

这一串密文中， `LyVpT/aetS`即为加入的 “盐”。

## 如何修改密码？

`tom:$6$iXDRKGEq$3FdFbXuwnPk7lSozGCsIws3q/o3HhYYpdiKqt6cQ3yGMIQxMLO93KXRAgD5uJJaCQhvZOiuEwkh6ti8I3AYL50:17599:0:99999:7:::`

我在 linux 中添加了一个用户 tom 来作为演示。 这天 tom 忘记了自己的密码，很着急，想知道如何找回密码。我说，密码是找不回了，但是我可以帮你修改原来的密码。

于是乎，我把上面`apple`的散列值替换了 tom 的散列值。

`tom:$6$LyVpT/aetS$mTDFTG9SzM7iVdP7Kqz6q2lsvgqjA45qXDAEcIUV/eEAaOGreCbd1XMet8itx7z1XM1ZFCb3UUd3toBozQiuZ.:17599:0:99999:7:::`

“tom 你好， `apple`就是你现在的新密码了。”

[Red Hat Linux 进入单用户模式 修改 root 密码​jingyan.baidu.com](https://link.zhihu.com/?target=https%3A//jingyan.baidu.com/article/6181c3e080d479152ef153ac.html)

如果你没有超级用户权限，也忘了密码的话，可以启用单用户模式，上面是链接。

如果你有 sudo 权限，`sudo passwd root` 就行，这篇文章提供了一种新的视角，您就当科普文看吧。

> 另外，本来就是边玩边分享，遇到问题一个人研究后有了新发现很激动，想分享给大家，因为很少有人通过改 `/etc/shadow` 来改密码。雕虫小技，恕我班门弄斧了 。有一两个人的评论很恶意哦☺️。
