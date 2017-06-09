#include"StdAfx.h"
#include "MiniModeWnd.h"


CMiniModeWnd::CMiniModeWnd()
: m_strTransSelect(_T(""))
{
}

CMiniModeWnd::~CMiniModeWnd()
{
}

UILIB_RESOURCETYPE CMiniModeWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CMiniModeWnd::GetWindowClassName() const
{
	return _T("YDMiniModeWnd");
}

void CMiniModeWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CMiniModeWnd::InitWindow()
{

}

CDuiString CMiniModeWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("ydres\\YDMiniModeWnd.xml");
	return szBuf;
}

CDuiString CMiniModeWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CMiniModeWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CMiniModeWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	default:
		break;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT  CMiniModeWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CMiniModeWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CMiniModeWnd::OnClick(CControlUI* pSender)
{
	if (_tcsicmp(pSender->GetName(), _T("TransSelectButton1")) == 0)
	{
		::SendMessage(m_hMianWnd, WM_USER_TRANS_STRING_CHANGED, 1, 0);
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnMiniClose")) == 0)
	{
		//Ö»Òþ²Ø²»Close
		::ShowWindow(this->m_hWnd,SW_HIDE);
		//Close();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnMiniQcsprig")) == 0)
	{
		CButtonUI *pBtnMiniQcsprig = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnMiniQcsprig")));
		CButtonUI *pBtnMiniQcfix = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnMiniQcfix")));
		pBtnMiniQcsprig->SetVisible(FALSE);
		pBtnMiniQcfix->SetVisible(TRUE);
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnMiniQcfix")) == 0)
	{
		CButtonUI *pBtnMiniQcsprig = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnMiniQcsprig")));
		CButtonUI *pBtnMiniQcfix = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnMiniQcfix")));
		pBtnMiniQcsprig->SetVisible(TRUE);
		pBtnMiniQcfix->SetVisible(FALSE);
	}
}
void  CMiniModeWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CMiniModeWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CMiniModeWnd::OnTimer(TNotifyUI& msg)
{

}

void CMiniModeWnd::SetMainWnd(HWND hWnd)
{
	m_hMianWnd = hWnd;
}

void CMiniModeWnd::HideWindow()
{
	::ShowWindow(this->m_hWnd,SW_HIDE);
}