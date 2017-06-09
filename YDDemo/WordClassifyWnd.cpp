#include"StdAfx.h"
#include "WordClassifyWnd.h"


CWordClassifyWnd::CWordClassifyWnd()
: m_strTransSelect(_T(""))
{
}

CWordClassifyWnd::~CWordClassifyWnd()
{
}

UILIB_RESOURCETYPE CWordClassifyWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CWordClassifyWnd::GetWindowClassName() const
{
	return _T("YDWordClassifyWnd");
}

void CWordClassifyWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CWordClassifyWnd::InitWindow()
{

}

CDuiString CWordClassifyWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("ydres\\YDWordClassifyWnd.xml");
	return szBuf;
}

CDuiString CWordClassifyWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CWordClassifyWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CWordClassifyWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:	
		::ShowWindow(this->m_hWnd,SW_HIDE);
		break;

	default:
		break;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT  CWordClassifyWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CWordClassifyWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CWordClassifyWnd::OnClick(CControlUI* pSender)
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}
void  CWordClassifyWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CWordClassifyWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CWordClassifyWnd::OnTimer(TNotifyUI& msg)
{

}

void CWordClassifyWnd::SetMainWnd(HWND hWnd)
{
	m_hMianWnd = hWnd;
}

void CWordClassifyWnd::HideWindow()
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}