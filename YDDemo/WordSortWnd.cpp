#include"StdAfx.h"
#include "WordSortWnd.h"


CWordSortWnd::CWordSortWnd()
: m_strTransSelect(_T(""))
{
}

CWordSortWnd::~CWordSortWnd()
{
}

UILIB_RESOURCETYPE CWordSortWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CWordSortWnd::GetWindowClassName() const
{
	return _T("YDWordSortWnd");
}

void CWordSortWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CWordSortWnd::InitWindow()
{

}

CDuiString CWordSortWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("YDWordSortWnd.xml");
	return szBuf;
}

CDuiString CWordSortWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CWordSortWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CWordSortWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT  CWordSortWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CWordSortWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CWordSortWnd::OnClick(CControlUI* pSender)
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}
void  CWordSortWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CWordSortWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CWordSortWnd::OnTimer(TNotifyUI& msg)
{

}

void CWordSortWnd::SetMainWnd(HWND hWnd)
{
	m_hMianWnd = hWnd;
}

void CWordSortWnd::HideWindow()
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}