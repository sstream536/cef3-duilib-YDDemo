#include "LoginWnd.h"


CLoginWnd::CLoginWnd()
{
}

CLoginWnd::~CLoginWnd()
{
}

UILIB_RESOURCETYPE CLoginWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CLoginWnd::GetWindowClassName() const
{
	return _T("YDLoginWnd");
}

void CLoginWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CLoginWnd::InitWindow()
{

}

CDuiString CLoginWnd::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("ydres\\YDLoginWnd.xml");
	return szBuf;
}

CDuiString CLoginWnd::GetSkinFolder()
{
	return _T("");
}


CControlUI* CLoginWnd::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT  CLoginWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT  CLoginWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


void  CLoginWnd::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);		
	}
}

void CLoginWnd::OnClick(CControlUI* pSender)
{
	if (_tcsicmp(pSender->GetName(), _T("BthLoginWndClose")) == 0)
	{
		Close();
	}
}
void  CLoginWnd::OnPrepare(TNotifyUI& msg)
{

}
void  CLoginWnd::OnExit(TNotifyUI& msg)
{
	Close();
}

void  CLoginWnd::OnTimer(TNotifyUI& msg)
{

}

