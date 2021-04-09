> @Date    : 2021-03-30 14:52:14
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# WSL2 开机启动 cron

> 原文：https://blog.csdn.net/weixin_43354181/article/details/105352203 [quantLearner](https://blog.csdn.net/The_Time_Runner) 2021-01-29 20:25:06

## Overview

每次关机重启之后，`wsl` 里面的 `cron` 服务是关闭的，如果忘记开启，就会导致定时任务失败。

首先要明确跟随谁启动：

1. `wsl` 里的 `cron` 服务跟随 `wsl` 自启动
2. `wsl` 里的 `cron` 服务跟随 `Window10` 自启动

## Starting Linux Background Services on Windows Login

WSL now have supports for background tasks when all your Linux console windows are closed. However, you still needed to start those services yourself because Linux sessions could only be initiated explicitly. There was no start-up config to launch services.

Here is how you can start WSL background services on Windows login:

### First, you’ll need a startup script

```Bash
# create a file named start_cron.sh and put it in ~/.local/bin/
echo "service cron start" >> ~/.local/bin/start_cron.sh
chmod +x ~/.local/bin/start_cron.sh
```

Running service requires `sudo` privledges. But, since we need to run this at start-up without interaction, so we should enable password-less `sudo`.

### Second, enable password-less sudo for specific commands

```Bash
# Open visudo to edit your sudo config
sudo visudo
# add this line to enable sudo run only this script, replace userid with your own
userid ALL=(root) NOPASSWD: /home/userid/.local/bin/start_cron.sh
```

### Third, get Windows to run this script in the WSL layer when you login

We can use the *Task Scheduler* to do this, so open the start menu and type "Task Scheduler(任务计划程序)" to find the application and run it.

> 任务计划程序库 --> 创建任务
> 
> 常规：start_cron
> 
> 触发器：新建 >> 登录时 >> 确定
> 
> 操作：新建 >> 启动程序 >> 程序或脚本 (`C:\Windows\System32\bash.exe`)>> 参加参数 (`-c"sudo ~/.local/bin/start_cron.sh"`)

## References

1. [WSl Tips: Starting Linux Background Services on Windows Login](https://dev.to/ironfroggy/wsl-tips-starting-linux-background-services-on-windows-login-3o98)
2. [Ubuntu 18.04 on WSL cron daemon not running after reboot](https://askubuntu.com/questions/1165969/ubuntu-18-04-on-wsl-cron-daemon-not-running-after-reboot)
