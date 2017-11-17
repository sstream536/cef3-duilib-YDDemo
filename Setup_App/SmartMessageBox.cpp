#include"SmartMessageBox.h"

SmartMessageBox::SmartMessageBox()
{
}

SmartMessageBox::~SmartMessageBox()
{
}

LPCTSTR SmartMessageBox::GetWindowClassName() const
{
	return _T("SMART_MESSAGE_BOX");
}

CControlUI* SmartMessageBox::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void SmartMessageBox::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString SmartMessageBox::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("msgBox.xml");
	return szBuf;
}

CDuiString SmartMessageBox::GetSkinFolder()
{
	return _T("");
}

UILIB_RESOURCETYPE SmartMessageBox::GetResourceType() const
{
	return UILIB_FILE;
}

LRESULT SmartMessageBox::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT SmartMessageBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT SmartMessageBox::ResponseDefaultKeyEvent(WPARAM wParam)
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

void SmartMessageBox::OnTimer(TNotifyUI& msg)
{
}

void SmartMessageBox::OnExit(TNotifyUI& msg)
{
	Close();
}

void SmartMessageBox::InitWindow()
{
}

void SmartMessageBox::OnPrepare(TNotifyUI& msg)
{
}

void SmartMessageBox::Notify(TNotifyUI& msg){
	if (msg.sType == _T("click")){
		OnClick(msg.pSender);
	}
	else if (msg.sType ==  _T("selectchanged"))
	{
		OnSelChanged(msg.pSender);
	}
}

LRESULT SmartMessageBox::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void SmartMessageBox::OnClick(CControlUI * spender){
	if (spender->GetName() == _T("btn_close")){
		::ShowWindow(SmartMessageBox::getInstance(), SW_HIDE);
		m_close_main_frame(false);
	}
	else if (spender->GetName() == _T("btn_ok")){
		m_close_main_frame(true);
	}
	else if (spender->GetName() == _T("btn_cancel")){
		m_close_main_frame(false);
		::ShowWindow(SmartMessageBox::getInstance(), SW_HIDE);
	}
	
}


void SmartMessageBox::OnSelChanged(CControlUI * spender){
}

