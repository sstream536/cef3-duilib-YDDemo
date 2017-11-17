#include "stdafx.h"
#include <windows.h>
#include "MainFrame.h"
#include "UnInstall.h"
#include "Ecoder.h"
#include <shellapi.h>
#include <Shlobj.h>  
#include <tchar.h>  
#include <Commctrl.h>  
#include <direct.h> 
#include <sstream>
#include <winuser.h>
#include "resource.h"
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
	return _T("");
}

UILIB_RESOURCETYPE MainFrame::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
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

	if (m_uninstall_thread){
		m_uninstall_thread->join();
		m_uninstall_thread.reset();
	}
	Close();
}

void MainFrame::InitWindow()
{
	static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("wizard_setup_tab")))->SelectItem(3);

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
		UnInstall::getInstance().setCallBack(std::bind(&MainFrame::setProcessCallBack,this,std::placeholders::_1,std::placeholders::_2),
			                                 std::bind(&MainFrame::setupEndCallBack, this));
		m_uninstall_thread.reset(new std::thread(std::mem_fn(&MainFrame::unInstall), this));
	}
	else if (spender->GetName() == _T("btn_cancle")){
		Close();
	}
	else if (spender->GetName() == _T("btn_uninstalled")){
	}
}

void MainFrame::unInstall(){
	UnInstall::getInstance().unInstall();
}


void MainFrame::OnSelChanged(CControlUI * spender){
	if (spender->GetName() == _T("ckbox_agree")){
		bool is_check = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->IsSelected();
		static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->SetCheck(is_check);
		if (is_check){
			std::wstring str = _T("form\\btn_UnInstallation_normal.png");
			static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_UnInstall")))->SetNormalImage(str.c_str());
		}
		else {
			std::wstring str = _T("form\\btn_UnInstallation_disable.png");
			static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_UnInstall")))->SetNormalImage(str.c_str());
		}
	}
}

void MainFrame::setupEndCallBack(){
	CTabLayoutUI * setup_tab = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("wizard_setup_tab")));
	setup_tab->SelectItem(5);
}

void MainFrame::setProcessCallBack(int process, const std::string & info){
	CSliderUI * slider = static_cast<CSliderUI*>(m_PaintManager.FindControl(_T("slr_uninst_progress")));
	slider->SetValue(process);
	std::stringstream stream;
	stream << process;
	std::string text;
	stream >> text;
	text = "%" + text;
	static_cast<CControlUI*>(m_PaintManager.FindControl(_T("un_progress_pos")))->SetText(Ecoder::stringToWstring(text).c_str());
	
}