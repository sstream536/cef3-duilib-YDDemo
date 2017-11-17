#include "stdafx.h"
#include <windows.h>
#include "MainFrame.h"
#include "Install.h"
#include "Ecoder.h"
#include <shellapi.h>
#include <Shlobj.h>  
#include <tchar.h>  
#include <Commctrl.h>  
#include <direct.h> 
#include <sstream>
#include "SmartMessageBox.h"

#pragma comment(lib, "comctl32.lib") 

MainFrame::MainFrame()
	:m_is_shortcut(true), m_is_agree(true), m_install_path("C:\\Program Files (x86)")
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
	Install::getInstance().setStop();
	if (m_install_thread){
		m_install_thread->join();
		m_install_thread.reset();
	}
	Close();
}

void MainFrame::InitWindow()
{
	static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->SetCheck(true);
	static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_shortcut")))->SetCheck(true);
	static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("edit_dir")))->SetText(Ecoder::stringToWstring(m_install_path).c_str());
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

void  MainFrame::closeMainFrameCallBack(bool is_close){
	if (is_close){
		Close();
	}
	else{
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_close")))->SetEnabled(true);
	}
}

void MainFrame::OnClick(CControlUI * spender){
	if (spender->GetName() == _T("btn_close")){
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_close")))->SetEnabled(false);
		static int smart_message_box_create = 0;
		if (smart_message_box_create++ == 0){
			SmartMessageBox::getInstance().Create(NULL, _T("SmartMessageBox"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
			SmartMessageBox::getInstance().CenterWindow();
		}
		SmartMessageBox::getInstance().setCallBack(std::bind(&MainFrame::closeMainFrameCallBack, this, std::placeholders::_1));
		::ShowWindow(SmartMessageBox::getInstance(), SW_SHOW);
	}
	else if (spender->GetName() == _T("btn_min")){
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else if(spender->GetName() == _T("btn_show_more")){		
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("more_config_info")))->SetVisible(true);
		RECT rect;
		GetWindowRect(this->m_hWnd, &rect);
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top + 70;
		::MoveWindow(this->m_hWnd, rect.left, rect.top, nWidth, nHeight, TRUE);
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_show_more")))->SetVisible(false);
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_hide_more")))->SetVisible(true);
	}
	else if (spender->GetName() == _T("btn_hide_more")){
		RECT rect;
		GetWindowRect(this->m_hWnd, &rect);
		int nWidth = rect.right - rect.left;
		int nHeight = rect.bottom - rect.top - 70;
		::MoveWindow(this->m_hWnd, rect.left, rect.top, nWidth, nHeight, TRUE);
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_hide_more")))->SetVisible(false);
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("btn_show_more")))->SetVisible(true);
		static_cast<CControlUI*>(m_PaintManager.FindControl(_T("more_config_info")))->SetVisible(false);
	}
	else if (spender->GetName() == _T("btn_agreement")){
		wchar_t szPathTemp[512];
		GetModuleFileName(NULL, szPathTemp, 512);
		string path = Ecoder::wstringToString(szPathTemp);
		size_t pos = path.rfind("\\");
		path = path.substr(0, path.length() - (path.length() - pos));
		path += "\\license.txt";
		ShellExecute(NULL, _T("open"), Ecoder::stringToWstring(path).c_str(), NULL, NULL, SW_SHOW);
	}
	else if (spender->GetName() == _T("btn_select_dir")){
		LPITEMIDLIST pil = NULL;
		INITCOMMONCONTROLSEX InitCtrls = { 0 };
		wchar_t sz_buf[4096] = { 0 };
		BROWSEINFO bi = { 0 };
		bi.hwndOwner = NULL;
		bi.iImage = 0;
		bi.lParam = NULL;
		bi.lpfn = NULL;
		bi.lpszTitle = _T("请选择安装目录");
		bi.pszDisplayName = sz_buf;
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
		InitCommonControlsEx(&InitCtrls);
		pil = SHBrowseForFolder(&bi);
		if (NULL != pil){
			SHGetPathFromIDList(pil, sz_buf);
			m_install_path = Ecoder::wstringToString(sz_buf).c_str();
			static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("edit_dir")))->SetText(sz_buf);
		}	
	}
	else if (spender->GetName() == _T("btn_install")){
		m_is_shortcut = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_shortcut")))->GetCheck();
		m_is_agree = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->GetCheck();
		std::wstring str_path = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("edit_dir")))->GetText().GetData();
		WIN32_FIND_DATA wfd;
		bool is_exit_dir = false;
		HANDLE hwd_find = FindFirstFile(str_path.c_str(), &wfd);
		if ((hwd_find != INVALID_HANDLE_VALUE) &&
			(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
			is_exit_dir = true;
		}
		
		FindClose(hwd_find);
		string install_path = Ecoder::wstringToString(str_path);;
		if (!is_exit_dir){
			if (mkdir(install_path.c_str()) == 0){
				is_exit_dir = true;
			}
		}
		install_path += "\\YDDemo";
		if (mkdir(install_path.c_str()) == 0){
			is_exit_dir = true;
		}
		//
		if (m_is_agree && is_exit_dir){
			m_install_thread.reset(new std::thread(std::mem_fn(&MainFrame::install), this));
			CTabLayoutUI* setup_tab = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("wizard_setup_tab")));
			setup_tab->SelectItem(1);
		}
	}
	else if (spender->GetName() == _T("btn_exec")){
		std::string str_tmp = m_install_path + "\\";
		m_install_path += "\\YDDemo.exe";
		ShellExecute(NULL, L"open", Ecoder::stringToWstring(m_install_path).c_str(), NULL, Ecoder::stringToWstring(str_tmp).c_str(), SW_SHOWNORMAL);
		Close();
	}
}

void MainFrame::install(){
	std::wstring str_path = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("edit_dir")))->GetText().GetData();
	string install_path = Ecoder::wstringToString(str_path);;
	install_path +="\\YDDemo";
	m_install_path = install_path;
	Install::getInstance().setCallBack(std::bind(&MainFrame::setProcessCallBack,this,std::placeholders::_1,std::placeholders::_2),
									   std::bind(&MainFrame::setupEndCallBack,this));
	Install::getInstance().install(install_path, m_is_shortcut);
}


void MainFrame::OnSelChanged(CControlUI * spender){
	if (spender->GetName() == _T("ckbox_agree")){
		bool is_check = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->IsSelected();
		static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("ckbox_agree")))->SetCheck(is_check);
		if (is_check){
			std::wstring str = _T("form\\btn_installation_normal.png");
			static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_install")))->SetNormalImage(str.c_str());
		}
		else {
			std::wstring str = _T("form\\btn_installation_disable.png");
			static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_install")))->SetNormalImage(str.c_str());
		}

	}
}

void MainFrame::setupEndCallBack(){
	CTabLayoutUI * setup_tab = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("wizard_setup_tab")));
	setup_tab->SelectItem(2);
}

void MainFrame::setProcessCallBack(int process, const std::string & info){
	CSliderUI * slider = static_cast<CSliderUI*>(m_PaintManager.FindControl(_T("slr_progress")));
	slider->SetValue(process);
	std::stringstream stream;
	stream << process;
	std::string text;
	stream >> text;
	text = "%" + text;
	static_cast<CControlUI*>(m_PaintManager.FindControl(_T("progress_pos")))->SetText(Ecoder::stringToWstring(text).c_str());
	
}