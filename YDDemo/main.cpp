//
// main.cpp
#include "simple_app.h"
#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>

#include "..\DuiLib\Utils\WinImplBase.h"
#include "MainFrame.h"

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{

	CPaintManagerUI::SetInstance(hInstance);

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if( FAILED(Hr) ) return 0;

	CefMainArgs args(hInstance);

	//创建CefApp实例
	CefRefPtr<SimpleApp> app(new SimpleApp);

	// 这个函数的执行在browser进程时会立即返回，
	// 在子进程时会堵塞直到退出时返回。
	int exitCode = CefExecuteProcess(args, app, NULL);
	if (exitCode >= 0)
	{
		return exitCode;
	}

	//填充这个结构体，用于定制CEF的行为。
	CefSettings settings;

	//初始化CEF
	CefInitialize(args, settings, app, NULL);


	CMainFrame* pFrame = new CMainFrame();
	if( pFrame == NULL ) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
	pFrame->Create(NULL, _T("PLApp"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
#else
	pFrame->Create(NULL, _T("PLApp"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
	HICON hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	::SendMessage(*pFrame, STM_SETICON, IMAGE_ICON, (LPARAM)(UINT)hIcon);

	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);
	//执行消息循环,此时会堵塞，直到CefQuitMessageLoop()函数被调用。
	CefRunMessageLoop();


	// 关闭CEF，释放资源  
	CefShutdown();
	/*CPaintManagerUI::MessageLoop();*/

	return 0;
}