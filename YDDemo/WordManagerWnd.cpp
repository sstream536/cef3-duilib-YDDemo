#include"StdAfx.h"
#include "WordManagerWnd.h"


CWordManagerWnd::CWordManagerWnd()
: m_strTransSelect(_T(""))
{
}

CWordManagerWnd::~CWordManagerWnd()
{
}

UILIB_RESOURCETYPE CWordManagerWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CWordManagerWnd::GetWindowClassName() const
{
	return _T("YDWordManagerWnd");
}

void CWordManagerWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CWordManagerWnd::InitWindow()
{

}

CDuiString CWordManagerWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("ydres\\YDWordManagerWnd.xml");
	return szBuf;
}

CDuiString CWordManagerWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CWordManagerWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CWordManagerWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		::ShowWindow(this->m_hWnd, SW_HIDE);
		break;
	default:
		break;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT  CWordManagerWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CWordManagerWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CWordManagerWnd::OnClick(CControlUI* pSender)
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}
void  CWordManagerWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CWordManagerWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CWordManagerWnd::OnTimer(TNotifyUI& msg)
{

}

void CWordManagerWnd::SetMainWnd(HWND hWnd)
{
	m_hMianWnd = hWnd;
}

void CWordManagerWnd::HideWindow()
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}