#include "StdAfx.h"
#include <windows.h>
#include "MainFrame.h"
#include <shellapi.h>
#include <Shlobj.h>  
#include <tchar.h>  
#include <Commctrl.h>  
#include <direct.h> 
#include <sstream>
#include <winuser.h>
#include "PcmShowLabelUI.h"
#pragma comment(lib, "comctl32.lib") 

MainFrame::MainFrame()
{
}

MainFrame::~MainFrame()
{
	PostQuitMessage(0);
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("TXGuiFoundation");
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClass)
{  
	if (_tcsicmp(pstrClass, PcmShowLableUIInterface) == 0){
		return  new CPcmShowLableUI();
	}
	return NULL;
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString MainFrame::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("install.xml");
	return szBuf;
}

CDuiString MainFrame::GetSkinFolder()
{
	//return _T("");
	return _T("res\\res\\");
}

UILIB_RESOURCETYPE MainFrame::GetResourceType() const
{
	//return UILIB_ZIPRESOURCE;
	return UILIB_FILE;
}
LPCTSTR MainFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}


LRESULT MainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
		}
		else
		{
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT MainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MainFrame::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void MainFrame::OnTimer(TNotifyUI& msg)
{
}

void MainFrame::OnExit(TNotifyUI& msg)
{
	Close();
}

void MainFrame::InitWindow()
{

}

void MainFrame::OnPrepare(TNotifyUI& msg)
{}

void MainFrame::Notify(TNotifyUI& msg){
	if (msg.sType == _T("click")){
		OnClick(msg.pSender);
	}
	else if (msg.sType ==  _T("selectchanged"))
	{
		OnSelChanged(msg.pSender);
	}
}

LRESULT MainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void MainFrame::OnClick(CControlUI * spender){
	if (spender->GetName() == _T("btn_close")){
		Close();
	}
	else if (spender->GetName() == _T("btn_min")){
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else if(spender->GetName() == _T("btn_uninstall")){		
		static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("wizard_setup_tab")))->SelectItem(4);
	}
	else if (spender->GetName() == _T("btn_uninstalled")){
	}
	else if (spender->GetName() == _T("btn_cancle")){
		Close();
	}
}

void MainFrame::OnSelChanged(CControlUI * spender){
	if (spender->GetName() == _T("ckbox_agree")){
	}
}
