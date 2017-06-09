#include "simple_app.h"
#include "StdAfx.h"
#include "simple_handler.h"
#include "include/wrapper/cef_helpers.h"

SimpleApp::SimpleApp() 
{

}

void SimpleApp::OnContextInitialized() {

	//只运行在UI线程上
	CEF_REQUIRE_UI_THREAD();

//	//创建CefClient实例
//	CefRefPtr<SimpleHandler> handler(new SimpleHandler());
//
//	// 设置浏览器属性
//	CefBrowserSettings browser_settings;
//
//	// Information used when creating the native window.
//	CefWindowInfo window_info;
//	window_info.SetAsPopup(NULL, _T("cefsimple"));
//
//	// 创建浏览器窗口
//	CefBrowserHost::CreateBrowser(window_info
//		, handler
//		, _T("http://www.baidu.com")
//		, browser_settings
//		, NULL);
//
}