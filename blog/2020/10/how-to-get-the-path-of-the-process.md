> @Date    : 2020-10-11 20:37:05
>
> @Author  : Lewis Tian (taseikyo@gmail.com)
>
> @Link    : github.com/taseikyo

# 怎样获取进程的路径？

> 原文：https://bbs.csdn.net/topics/320198068

实际上是 CSDN 的一个讨论贴，应该是我去年保存为书签的，为了防止被删，直接做个 backup，以某种格式，看一条就知道了

@[lugaideath1](https://my.csdn.net/lugaideath1)，上面的是获取了系统的进程，但我同时想获得那些进程的路径，应该怎么写呢？【2009-11-26 10:46:32】

```C++
#include <windows.h>
#include <tlhelp32.h>

int main(int argc, char* argv[]) {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
	                      0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf(" CreateToolhelp32Snapshot调用失败！ \n");
		return -1;
	}

	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore) {
		printf(" 进程名称：%s \n", pe32.szExeFile);
		printf(" 进程ID号：%u \n\n", pe32.th32ProcessID);

		bMore = ::Process32Next(hProcessSnap, &pe32);
	}

	::CloseHandle(hProcessSnap);
	return 0;
}
```

@[老邓](https://my.csdn.net/Loaden)，【2009-11-26 11:38:53】

```C++
//获取进程路径
CString GetProcessPath( DWORD idProcess ) {
	// 获取进程路径
	CString sPath;
	// 打开进程句柄
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
	                               PROCESS_VM_READ, FALSE, idProcess );
	if ( NULL != hProcess ) {
		HMODULE hMod;
		DWORD cbNeeded;
		// 获取路径
		if ( EnumProcessModules( hProcess, &hMod, sizeof( hMod ),
		                         &cbNeeded ) ) {
			DWORD dw = GetModuleFileNameEx( hProcess, hMod, sPath.
			                                GetBuffer( MAX_PATH ), MAX_PATH );
			sPath.ReleaseBuffer();
		}
		CloseHandle( hProcess );
	}
	return ( sPath );
}

//获取进程优先级
CString GetProcessPriority(HANDLE hProcess) {
	char sz1[10] = "NORMAL";
	char sz2[10] = "IDLE";
	char sz3[10] = "REALTIME";
	char sz4[10] = "HIGH";
	char sz5[10] = "NULL";
	char sz6[15] = "ABOVENORMAL";
	char sz7[15] = "BELOWNORMAL";

	//进程优先级返回
	if (GetPriorityClass(hProcess) == NORMAL_PRIORITY_CLASS)
		return sz1;
	if (GetPriorityClass(hProcess) == IDLE_PRIORITY_CLASS)
		return sz2;
	if (GetPriorityClass(hProcess) == REALTIME_PRIORITY_CLASS)
		return sz3;
	if (GetPriorityClass(hProcess) == HIGH_PRIORITY_CLASS)
		return sz4;
	if (GetPriorityClass(hProcess) == ABOVE_NORMAL_PRIORITY_CLASS)
		return sz6;
	if (GetPriorityClass(hProcess) == BELOW_NORMAL_PRIORITY_CLASS)
		return sz7;
	else
		return sz5;
}

//终止进程主函数
void TerminateProcessID(DWORD dwID) {
	HANDLE hProcess = NULL;
	//打开进程句柄
	hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwID);
	if (hProcess != NULL) {
		//终止进程
		TerminateProcess(hProcess, 0);
		::CloseHandle(hProcess);
	}
}

//获取进程快照
void GetProcessInfo() {
	SHFILEINFO shSmall;
	int nIndex;
	CString str;
	//声明进程信息变量
	PROCESSENTRY32 ProcessInfo;
	//获取系统中的所有进程信息
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnapShot != NULL) {
		m_ListCtrl.DeleteAllItems();
		//设置ProcessInfo的大小
		ProcessInfo.dwSize = sizeof(PROCESSENTRY32);
		//返回系统中第一个进程的信息
		BOOL Status = Process32First(SnapShot, &ProcessInfo);
		//进程计数
		int m_nProcess = 0;
		while (Status) {
			m_nProcess++;
			ZeroMemory(&shSmall, sizeof(shSmall));
			//获取进程文件的信息
			SHGetFileInfo(ProcessInfo.szExeFile, 0, &shSmall,
			              sizeof(shSmall), SHGFI_ICON | SHGFI_SMALLICON);
			//在列表控件中添加映像名称
			nIndex = m_ListCtrl.InsertItem(m_nProcess, ProcessInfo.szExeFile);
			//在列表控件中添加进程PID
			str.Format("%08X", ProcessInfo.th32ProcessID);
			m_ListCtrl.SetItemText(nIndex, 1, str);
			//在列表控件中添加进程的父进程PID
			str.Format("%08X", ProcessInfo.th32ParentProcessID);
			m_ListCtrl.SetItemText(nIndex, 2, str);
			//获取进程路径
			str = GetProcessPath(ProcessInfo.th32ProcessID);
			m_ListCtrl.SetItemText(nIndex, 3, str);
			//获取下一个进程信息
			Status = Process32Next(SnapShot, &ProcessInfo);
		}
	} else
		MessageBox("获取进程信息失败!");
}

//获取模块快照
void GetProcessModule(DWORD dwID) {
	MODULEENTRY32 me32;
	int nIndex;
	CString str;

	// 在使用这个结构之前，先设置它的大小
	me32.dwSize = sizeof(me32);

	// 给进程内所有模块拍一个快照
	HANDLE hModuleSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
	                     dwID);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		//建立快照失败
		MessageBox("获取模块信息失败!", "提示",
		           MB_OK | MB_ICONWARNING);
		return;
	}

	// 遍历模块快照，轮流显示每个模块的信息
	BOOL bMore = Module32First(hModuleSnap, &me32);
	int m_nModule = 0;
	while (bMore) {
		m_nModule++;
		nIndex = m_listmod.InsertItem(m_nModule,
		                              me32.szExePath);//模块路径
		str.Format("%u", me32.modBaseSize);//模块大小
		m_listmod.SetItemText(nIndex, 1, str);
		bMore = Module32Next(hModuleSnap, &me32);
	}
	// 不要忘记清除掉snapshot对象
	CloseHandle(hModuleSnap);
}

//
// FindProcess
// 这个函数唯一的参数是你指定的进程名，如:你的目标进程
// 是 "Notepad.exe",返回值是该进程的ID，失败返回0
//

DWORD FindProcess(char *strProcessName) {
	DWORD aProcesses[1024], cbNeeded, cbMNeeded;
	HMODULE hMods[1024];
	HANDLE hProcess;
	char szProcessName[MAX_PATH];

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses),
	                     &cbNeeded ) )  return 0;
	for (int i = 0; i < (int) (cbNeeded / sizeof(DWORD)); i++) {
		//_tprintf(_T("%d "), aProcesses[i]);
		hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		                         FALSE, aProcesses[i]);
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		GetModuleFileNameEx( hProcess, hMods[0], szProcessName,
		                     sizeof(szProcessName));

		if (strstr(szProcessName, strProcessName)) {
			//_tprintf(_T("%s;"), szProcessName);
			return (aProcesses[i]);
		}
		//_tprintf(_T(" "));
	}
	return 0;
}

//
// KillProcess
// 此函数中用上面的 FindProcess 函数获得你的目标进程的ID
// 用WIN API OpenPorcess 获得此进程的句柄，再以TerminateProcess
// 强制结束这个进程
//

VOID KillProcess() {
	// When the all operation fail this function terminate the "winlogon" Process for force exit the system.
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE,
	                               FindProcess("YourTargetProcess.exe"));

	if (hYourTargetProcess == NULL) {
		return;
	}

	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);

	return;
}

本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/zltpc007/archive/2008/01/05/2026549.aspx
```

@[lugaideath1](https://my.csdn.net/lugaideath1)，【2009-11-26 14:39:23】

```C++
#include "widget.h"
#include "ui_widget.h"
#include <QProcess>

Widget::Widget(QWidget *parent)
	: QWidget(parent), ui(new Ui::Widget) {
	ui->setupUi(this);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotGet()));
	connect(ui->pushButton_2, SIGNAL(clicked()), this,
	        SLOT(slotDelete()));
//    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(slotGetPath()));

#ifdef Q_WS_X11
	qDebug() << "X11";
#endif

#ifdef Q_WS_WIN
	qDebug() << "Win";
#endif

}

void Widget::slotGet() {
	ui->listWidget->clear();
	this->processID.clear();

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
	                      0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot 调用失败");
		return;
	}
	bool bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore) {
		ui->listWidget->addItem(QString::fromWCharArray(pe32.szExeFile));
		this->processID << pe32.th32ProcessID;
		qDebug() <<  GetProcessPath(pe32.th32ProcessID);
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}

	::CloseHandle(hProcessSnap);
}

void Widget::slotDelete() {
	if (ui->listWidget->selectionModel()->selection().isEmpty())
		return;

	int result = QMessageBox::question(this, tr("温馨提示"),
	                                   tr("你确定要结束《%1》进程吗？").arg(
	                                       ui->listWidget->currentItem()->text()),
	                                   QMessageBox::Yes | QMessageBox::No);
	if (result == QMessageBox::No)
		return;

	DWORD dwProcessID = this->processID.at(ui->listWidget->currentRow());
	HANDLE hProcessSnap = OpenProcess(PROCESS_TERMINATE, false,
	                                  dwProcessID);
	bool deleteResult = ::TerminateProcess(hProcessSnap, 0);
	::CloseHandle(hProcessSnap);
	if (deleteResult)
		QMessageBox::information(this, tr("温馨提示"),
		                         tr("成功结束进程！"));
	else {
		QMessageBox::critical(this, tr("执行失败"),
		                      tr("结束进程失败！"));
		return;
	}

	this->slotGet();
}

void Widget::slotGetPath() {
	if (ui->listWidget->selectionModel()->selection().isEmpty())
		return;

	TCHAR name[255];
	DWORD dwProcessID = this->processID.at(ui->listWidget->currentRow());
	HANDLE hProcessSnap = OpenProcess(PROCESS_QUERY_INFORMATION |
	                                  PROCESS_VM_READ, false, dwProcessID);
	::GetModuleFileName((HMODULE)hProcessSnap, name, 255);
	qDebug() << QString::fromWCharArray(name);
	::CloseHandle(hProcessSnap);
}

QString Widget::GetProcessPath( DWORD idProcess ) {
	// 获取进程路径
	WCHAR name[1024];
	ZeroMemory(name, 1024);
	// 打开进程句柄
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
	                               PROCESS_VM_READ, FALSE, idProcess );
	if ( NULL != hProcess ) {
		DWORD cbNeeded;
		HMODULE hMod;
		// 获取路径
		if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			DWORD dw = ::GetModuleFileNameExW(hProcess, hMod, name, 1024 );

		CloseHandle( hProcess );
	}
	return QString::fromWCharArray(name);
}

Widget::~Widget() {
	delete ui;
}
```

@[老邓](https://my.csdn.net/Loaden)，这是一个完整的Demo代码，把PID改一下后再测试。其中PID可以根据任务管理器查看。【2009-11-26 14:58:45】

```C++
#ifndef WINVER
#define WINVER 0x0500
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0500
#endif

#include <windows.h>
#include <iostream>

#include <psapi.h>
#pragma comment(lib, "psapi.lib")

using namespace std;

int main() {
	const DWORD dwProcessId = 6076;
	TCHAR modulePath[MAX_PATH];
	// 打开进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
	                              PROCESS_VM_READ, FALSE, dwProcessId);
	if (NULL != hProcess) {
		DWORD cbNeeded;
		HMODULE hMod;
		// 获取路径
		if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			DWORD dw  = ::GetModuleFileNameEx(hProcess, hMod, modulePath,
			                                  MAX_PATH);
		MessageBox(0, modulePath, 0, 0);

		CloseHandle(hProcess);
	}

	return 0;
}
```
