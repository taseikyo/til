> @Date    : 2020-09-14 11:14:16
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# PowerShell 设置命令别名

> 原文：https://segmentfault.com/a/1190000015928399 作者：[SilentGene
](https://segmentfault.com/u/silentgene) 2018-08-08

## Table of Contents

- [前言](#前言)
- [查看别名](#查看别名)
- [创建或更改别名](#创建或更改别名)
	- [创建不带参数的别名](#创建不带参数的别名)
	- [创建或更改带参数的别名](#创建或更改带参数的别名)
- [删除别名](#删除别名)
- [创建永久的别名](#创建永久的别名)

## 前言

`PowerShell` 在 Windows10 中的地位被慢慢提高，在最近的系统版本中，Powershell 已经在资源管理器中完全代替以前的 `cmd` 出现。所以我本人也逐渐把运行命令的习惯向 PowerShell 迁移。

在使用过程中发现 PowerShell 虽然默认支持类似 Unix 系统的 `ls` 命令，但是其默认展示方式是非常详细的，包括 `Mode`，`LastWriteTime`,`Length` 和 `Name` 共 4 个字段。这里的 `ls` 其实是 PowerShell 命令 `Get-ChildItem` 的一个别名，显示效果如下：

```bash
PS D:\apktool> get-childitem


    Directory: D:\apktool


Mode                LastWriteTime         Length Name
----                -------------         ------ ----
-a----        2/23/2016     20:15            159 apktool.bat
-a----        2/23/2016     20:16        6433219 apktool.jar
```

而在实际工作中，其实我是比较喜欢用 `ls` 命令只显示文件名。那么在 PowerShell 中默认的命令需要输入`ls -Name` 或 `Get-ChildItem -Name` 来实现。

下面来说说一些关于 PowerShell 中设置命令别名 Alias 的常用相关命令和方法：

*以下命令中的大小写不敏感*

## 查看别名

- 查看此 Session 中已经设定的所有别名：`Get-Alias` 或 `gal`

```bash
PS C:\> Get-Alias
CommandType     Name
-----------     ----
Alias           % -> ForEach-Object
Alias           ? -> Where-Object
Alias           ac -> Add-Content
Alias           asnp -> Add-PSSnapin
```

- 查看某别名的原命令，如 `ls` 的原命令：`> Get-Alias ls`
- 查看某原命令的别名，如 `Get-ChildItem` 的别名：`> Get-Alias -Definition Get-ChildItem`

## 创建或更改别名

### 创建不带参数的别名

使用 `Set-Alias` 命令创建或更改别名。注意使用该命令设定的别名只在目前的 Windows PowerShell session 中生效。也就是说在关闭此会话后这个别名将会失效。如何创建永久的别名？往下看。

如为 `Get-ChildItem` 命令设定别名 `list`：

```bash
PS C:\> Set-Alias -Name list -Value get-childitem
```

或简单一些：

```bash
PS C:\> Set-Alias list get-childitem
```

*注意：对于系统默认设定的别名，不可在删除此别名之前重新对这个别名赋值。*

另外，PowerShell 中还有一个命令 `New-Alias`，该命令和 `Set-Alias` 基本功能一样，只是前者不能**更改**别名，只能**创建**别名。当试图使用 `New-Alias` 命令创建已存在的别名时，会报错。

### 创建或更改带参数的别名

如果命令带参数如想为 `Get-ChildItem -Name` 设定别名为 `ls` 则我们需要两步，第一步为这个带参数原命令设定一个中间 `function`，第二步为这个 function 指定别名：

```bash
PS C:\> function getlist {Get-ChildItem -Name}
PS C:\> Set-Alias ls getlist
```

## 删除别名

使用 `Remove-Item alias` 命令删除已设定的别名。

如删除别名 `ls`：

```bash
PS C:\> Remove-Item alias:ls
```

## 创建永久的别名

在 PowerShell 中直接使用 `Set-Alias` 或 `New-Alias` 命令创建的别名在关闭此 Session 后即会失效，防止此现象的方法是将此命令写入 `Windows PowerShell profile` 文件。

查看此文件在计算机中的位置：

```bash
PS C:\> $profile
```

一般该文件在没有创建前是不存在的，使用以下命令为当前用户创建 profile 命令并返回文件地址：

```bash
PS C:\> New-Item -Type file -Force $profile
```

一般创建的位置在 `~\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1`

打开文件，键入文件内容为 `Get-ChildItem -Name` 创建别名 `ls`：

```bash
function getFileName{
    Get-ChildItem -Name
}
Remove-Item alias:ls
Set-Alias ls getFileName
```

这里首先为 `Get-ChildItem -Name` 创建了方法 `getFileName`作为中介，然后为该方法赋予别名 `ls`，但是因为 `ls` 是 Windows PowerShell 中的默认别名，因此必须先删除再创建，所以先使用 `Remove-Item` 再使用 `Set-Alias` 或 `New-Alias`。

以后每次在打开 PowerShell 会话框的时候其会先读取 `$profile` 文件中的内容。

试试效果：

```bash
PS D:\apktool> ls
apktool.bat
apktool.jar
```