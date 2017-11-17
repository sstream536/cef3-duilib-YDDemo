#include"StdAfx.h"
#include "TransSelectWnd.h"


CTransSelectWnd::CTransSelectWnd()
: m_strTransSelect(_T(""))
{
}

CTransSelectWnd::~CTransSelectWnd()
{
}

UILIB_RESOURCETYPE CTransSelectWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CTransSelectWnd::GetWindowClassName() const
{
	return _T("YDTransSelectWnd");
}

void CTransSelectWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CTransSelectWnd::InitWindow()
{

}

CDuiString CTransSelectWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("YDTranSelectWnd.xml");
	return szBuf;
}

CDuiString CTransSelectWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CTransSelectWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CTransSelectWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT  CTransSelectWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CTransSelectWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CTransSelectWnd::OnClick(CControlUI* pSender)
{
	if (_tcsicmp(pSender->GetName(), _T("TransSelectButton1")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 1, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton2")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 2, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton3")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 3, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton4")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 4, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton5")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 5, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton6")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 6, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton7")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 7, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("TransSelectButton8")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 8, 0);
	}
	::ShowWindow(this->m_hWnd,SW_HIDE);
}
void  CTransSelectWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CTransSelectWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CTransSelectWnd::OnTimer(TNotifyUI& msg)
{

}

void CTransSelectWnd::SetMainWnd(HWND hWnd)
{
	m_hMianWnd = hWnd;
}

void CTransSelectWnd::HideWindow()
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}