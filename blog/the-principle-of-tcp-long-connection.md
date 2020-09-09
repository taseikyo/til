> @Date    : 2020-09-09 17:16:13
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

> 原文地址 [blog.csdn.net](https://blog.csdn.net/weixin_44857400/article/details/108083585) [The-Dean](https://me.csdn.net/weixin_44857400) 2020-08-20 01:15:53

# TCP 如何实现长连接

## 1. 应用层的心跳机制

通过应用程序自身发送心跳包去检测连接是否正常，基本方法就是在服务器端设置一个 Timer 事件，在一定时间段内向客户端一个心跳数据包，若在一定时间内没有收到客户端的回应，那么就会认为客户端掉线；同样客户端在一定时间段内没有收到服务器的心跳包，则判断与服务器端连接断开。
    
## 2. TCP 的 keepalive 机制

其实跟心跳机制大同小异，无论是客户端还是服务器端，只要有一方开启 Keepalive 功能后，就会在特定的时间段内发送心跳包，对端在收到心跳包后进行回复，表示自己在线。默认的 Keepalive 超时时间为 2 小时，探测次数为 5 次，但超时时间可以手动设置成合理的时间段。