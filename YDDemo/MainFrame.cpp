#include "simple_app.h"
#include "stdafx.h"
#include <windows.h>
#include "MainFrame.h"
#include "ButtonTab.h"
#include "LoginWnd.h"
#include "TransSelectWnd.h"
#include "WordClassifyWnd.h"
#include "WordSortWnd.h"
#include "WordManagerWnd.h"
#include "MiniModeWnd.h"
#include "simple_handler.h"
#include "include/wrapper/cef_helpers.h"


const TCHAR* const TitleControlName		    = _T("YDDemo");
const TCHAR* const CloseButtonControlName   = _T("BtnClose");
const TCHAR* const MinButtonControlName	    = _T("BtnMin");
const TCHAR* const MaxButtonControlName     = _T("BtnMax");
const TCHAR* const RestoreButtonControlName = _T("BtnRestore");

CefRefPtr<SimpleHandler> g_handler(new SimpleHandler());

CTransSelectWnd * g_pTransSelectFrame = NULL;
CWordClassifyWnd * g_pWordClassifyFrame = NULL;
CWordSortWnd * g_pWordSortFrame = NULL;
CWordManagerWnd * g_pWordManagerFrame = NULL;
CMiniModeWnd * g_pMiniModeFrame = NULL;
//
CTransSelectWnd* GetTransSelectInstance(CMainFrame *pMainFrame)
{
	if (g_pTransSelectFrame == NULL)
	{
		g_pTransSelectFrame = new CTransSelectWnd;
		g_pTransSelectFrame->Create(NULL, _T("TransSelectWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
		g_pTransSelectFrame->SetMainWnd(pMainFrame->GetMainWnd());
	}
	return g_pTransSelectFrame;
}

CWordClassifyWnd* GeWordClassifyInstance(CMainFrame *pMainFrame)
{
	if (g_pWordClassifyFrame == NULL)
	{
		g_pWordClassifyFrame = new CWordClassifyWnd;
		g_pWordClassifyFrame->Create(NULL, _T("WordClassifyWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
		g_pWordClassifyFrame->SetMainWnd(pMainFrame->GetMainWnd());
	}
	return g_pWordClassifyFrame;
}

CWordSortWnd* GetWordSortInstance(CMainFrame *pMainFrame)
{
	if (g_pWordSortFrame == NULL)
	{
		g_pWordSortFrame = new CWordSortWnd;
		g_pWordSortFrame->Create(NULL, _T("WordSortWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
		g_pWordSortFrame->SetMainWnd(pMainFrame->GetMainWnd());
	}
	return g_pWordSortFrame;
}

CWordManagerWnd* GetWordManagerInstance(CMainFrame *pMainFrame)
{
	if (g_pWordManagerFrame == NULL)
	{
		g_pWordManagerFrame = new CWordManagerWnd;
		g_pWordManagerFrame->Create(NULL, _T("WordManagerWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
		g_pWordManagerFrame->SetMainWnd(pMainFrame->GetMainWnd());
	}
	return g_pWordManagerFrame;
}

CMiniModeWnd* GetMiniModeInstance(CMainFrame *pMainFrame)
{
	if (g_pMiniModeFrame == NULL)
	{
		g_pMiniModeFrame = new CMiniModeWnd;
		g_pMiniModeFrame->Create(NULL, _T("MiniModeWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW);
		g_pMiniModeFrame->SetMainWnd(pMainFrame->GetMainWnd());
	}
	return g_pMiniModeFrame;
}

CMainFrame::CMainFrame()
:m_bIsInit(FALSE), m_pTransSelectFrame(NULL), m_pWordClassifyFrame(NULL), 
m_pWordSortFrame(NULL), m_pWordManagerFrame(NULL), m_pMiniModeFrame(NULL)
{
}

CMainFrame::~CMainFrame()
{
	PostQuitMessage(0);
}

LPCTSTR CMainFrame::GetWindowClassName() const
{
	return _T("YDCMainFrame");
}

void CMainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString CMainFrame::GetSkinFile()
{
	TCHAR szBuf[MAX_PATH] = _T("MainWindow.xml");
	return szBuf;
}

CDuiString CMainFrame::GetSkinFolder()
{
	return _T("");
}

UILIB_RESOURCETYPE CMainFrame::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR CMainFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}


CControlUI* CMainFrame::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("TbOptSearchWord")) == 0)
	{
		return new CButtonTab(&m_PaintManager);
	}
	return NULL;
}


LRESULT CMainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	AdjustCefWindow();
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(MaxButtonControlName));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(RestoreButtonControlName));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(MaxButtonControlName));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(RestoreButtonControlName));
			if( pControl ) pControl->SetVisible(false);
		}
	}
	
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif
	return 0;
}
void CMainFrame::UpdateTransString(int nNum)
{
	CButtonUI* pBtnTrans = static_cast <CButtonUI*>(m_PaintManager.FindControl(_T("BtnCvLg")));
	//
	switch (nNum)
	{
	case 1:
		pBtnTrans->SetText(_T("英汉互译"));
		break;
	case 2:
		pBtnTrans->SetText(_T("法汉互译"));
		break;
	case 3:
		pBtnTrans->SetText(_T("韩汉互译"));
		break;
	case 4:
		pBtnTrans->SetText(_T("日汉互译"));
		break;
	case 5:
		pBtnTrans->SetText(_T("德汉互译"));
		break;
	case 6:
		pBtnTrans->SetText(_T("俄汉互译"));
		break;
	case 7:
		pBtnTrans->SetText(_T("葡汉互译"));
		break;
	case 8:
		pBtnTrans->SetText(_T("西汉互译"));
		break;
	default:
		break;
	}
}
//
void CMainFrame::HideLayoutFrame()
{
	if (m_pTransSelectFrame != NULL)
	{
		::ShowWindow(*m_pTransSelectFrame, SW_HIDE);
		m_pTransSelectFrame = NULL;
	}
	if (m_pWordClassifyFrame != NULL)
	{
		::ShowWindow(*m_pWordClassifyFrame, SW_HIDE);
		m_pWordClassifyFrame = NULL;
	}
	if (m_pWordSortFrame != NULL)
	{
		::ShowWindow(*m_pWordSortFrame, SW_HIDE);
		m_pWordSortFrame = NULL;
	}
	if (m_pWordManagerFrame != NULL)
	{
		::ShowWindow(*m_pWordManagerFrame, SW_HIDE);
		m_pWordManagerFrame = NULL;
	}
}
//
LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_SIZE:
		OnSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_USER_TRANS_STRING_CHANGED:
		UpdateTransString(wParam);
		break;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainFrame::ResponseDefaultKeyEvent(WPARAM wParam)
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

void CMainFrame::OnTimer(TNotifyUI& msg)
{
}

void CMainFrame::OnExit(TNotifyUI& msg)
{
	Close();
}

void CMainFrame::AdjustCefWindow()
{
	if (m_bIsInit)
	{
		CefRefPtr<CefBrowser> browser = g_handler->GetCurrentBrowser();
		if (browser != NULL)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			if (hwnd)
			{
				RECT rect;
				GetClientRect(this->m_hWnd, &rect);
				int nWidth = rect.right - rect.left - 140;
				int nHeight = rect.bottom - rect.top - 60;
				::MoveWindow(hwnd,140,60, nWidth, nHeight, TRUE);
			}
		}
	}
}

LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	AdjustCefWindow();
	__super::OnSize(uMsg, wParam, lParam, bHandled);
	return 0;
}

void CMainFrame::InitWindow()
{
	m_bIsInit = TRUE;
	FirstLoadCef();
}

void CMainFrame::OnPrepare(TNotifyUI& msg)
{
}

void CMainFrame::FirstLoadCef()
{
	CTabLayoutUI* pTabTest = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));
	COptionUI *pTbOptSearchWord = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("TbOptSearchWord")));
	if (pTabTest == NULL)
	{
		return;
	}
	RECT rect;
	GetClientRect(this->m_hWnd, &rect);
	int nCx = GetSystemMetrics(SM_CXFULLSCREEN);
	int nCy = GetSystemMetrics(SM_CYFULLSCREEN);

	RECT rt;
	rt.left = rect.left+ 140;
	rt.top =  rect.top + 60;

	rt.bottom = rt.top + 600-60;
	rt.right = rt.left + 925-140;

	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(m_hWnd, rt);
	BOOL bSucced = CefBrowserHost::CreateBrowser(window_info
		, g_handler
		, _T("http://dict.youdao.com/?keyfrom=cidian")
		, browser_settings
		, NULL);
	pTabTest->SelectItem(0);
	pTbOptSearchWord->Selected(TRUE);
}
void CMainFrame::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClick(msg.pSender);
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		OnSelChanged(msg.pSender);
	}
}
void CMainFrame::OnClick(CControlUI * pSender)
{
	if (_tcsicmp(pSender->GetName(), _T("BtnMin")) == 0)
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);

		return;
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnMax")) == 0)
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		return;
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnRestore")) == 0)
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		return;
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnLoginInfo")) == 0
		|| _tcsicmp(pSender->GetName(), _T("BtnUserLogin")) == 0
		|| _tcsicmp(pSender->GetName(), _T("BtnWordSynchronized")) == 0)
	{
		CLoginWnd* pFrame = new CLoginWnd();
		pFrame->Create(this->m_hWnd, _T("LoginWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		pFrame->CenterWindow();
		pFrame->ShowModal();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnTransSelect")) == 0)
	{
		ShowTransSelectFrame();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnWordClassify")) == 0)
	{
		ShowWordClassifyFrame();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnWordSort")) == 0)
	{
		ShowWordSortFrame();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnWordManager")) == 0)
	{
		ShowWordManagerFrame();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnMiniMode")) == 0)
	{
		ShowMiniModeFrame();
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnWordPlanBack")) == 0)
	{
		CTabLayoutUI* pTabTest = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));
		pTabTest->SelectItem(4);
	}
	else if (_tcsicmp(pSender->GetName(), _T("BtnWordRecovery")) == 0)
	{
		CTabLayoutUI* pTabTest = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));
		pTabTest->SelectItem(8);
	}
	else if (_tcsicmp(pSender->GetName(),_T("BtnClose")) == 0)
	{
		Close();
	}
}

void CMainFrame::ShowTransSelectFrame()
{
	m_pTransSelectFrame = GetTransSelectInstance(this);
	RECT rect;
	GetClientRect(this->m_hWnd, &rect);
	POINT point = *((POINT *)&rect);
	ClientToScreen(this->m_hWnd, &point);
	::MoveWindow(*m_pTransSelectFrame, point.x + 200, point.y + 50, 335, 72, TRUE);
	m_pTransSelectFrame->ShowModal();
}

void CMainFrame::ShowWordClassifyFrame()
{
	m_pWordClassifyFrame = GeWordClassifyInstance(this);
	RECT rect;
	GetClientRect(this->m_hWnd, &rect);
	POINT point = *((POINT *)&rect);
	ClientToScreen(this->m_hWnd, &point);
	::MoveWindow(*m_pWordClassifyFrame, point.x + 170, point.y + 132, 135, 78, TRUE);
	m_pWordClassifyFrame->ShowModal();
}

void CMainFrame::ShowWordSortFrame()
{
	m_pWordSortFrame = GetWordSortInstance(this);
	RECT rect;
	GetClientRect(this->m_hWnd, &rect);
	POINT point = *((POINT *)&rect);
	ClientToScreen(this->m_hWnd, &point);
	::MoveWindow(*m_pWordSortFrame, point.x + 220, point.y + 132, 135, 210, TRUE);
	m_pWordSortFrame->ShowModal();
}
void CMainFrame::ShowWordManagerFrame()
{
	m_pWordManagerFrame = GetWordManagerInstance(this);
	CButtonUI* pBtnTransSelect = static_cast <CButtonUI*>(m_PaintManager.FindControl(_T("BtnTransSelect")));
	RECT rect;
	GetClientRect(this->m_hWnd, &rect);
	POINT point = *((POINT *)&rect);
	ClientToScreen(this->m_hWnd, &point);
	::MoveWindow(*m_pWordManagerFrame, point.x + 270, point.y + 132, 84, 210, TRUE);
	m_pWordManagerFrame->ShowModal();
}

void CMainFrame::ShowMiniModeFrame()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	m_pMiniModeFrame = GetMiniModeInstance(this);
	m_pMiniModeFrame->CenterWindow();
	m_pMiniModeFrame->ShowModal();
	//显示
	::ShowWindow(*m_pMiniModeFrame, SW_SHOW);
}

void CMainFrame::HideCefWindow()
{
	CefRefPtr<CefBrowser> browser = g_handler->GetCurrentBrowser();
	if (browser != NULL)
	{
		CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
		if (hwnd)
		{
			::ShowWindow(hwnd, SW_HIDE);
		}
	}
}

void CMainFrame::OnSelChanged(CControlUI* pSender)
{
	CTabLayoutUI* pTabTest = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));
	CTabLayoutUI* pTabSettings = static_cast <CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabSettings")));
	COptionUI *pTbOptSearchWord = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("TbOptSearchWord")));
	if (pTabTest == NULL)
	{
		return;
	}
	CDuiString strSelName = pSender->GetName();
	if (strSelName == _T("TbOptSearchWord")) 
	{
		CefRefPtr<CefBrowser> browser = g_handler->GetCurrentBrowser();
		if (browser != NULL)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			if (hwnd)
			{
				::ShowWindow(hwnd, SW_SHOW);
				browser->GetMainFrame()->LoadURL(_T("http://dict.youdao.com/?keyfrom=cidian"));
			}
		}
		pTabTest->SelectItem(0);
	}
	else if (strSelName == _T("OptionDemo2"))
	{
		CefRefPtr<CefBrowser> browser = g_handler->GetCurrentBrowser();
		if (browser != NULL)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			if (hwnd)
			{
				::ShowWindow(hwnd, SW_SHOW);
				browser->GetMainFrame()->LoadURL(_T("http://fanyi.youdao.com/?keyfrom=dict2.index"));
			}
		}
		pTabTest->SelectItem(1);
	}
	else if (strSelName == _T("OptionDemo3"))
	{
		HideCefWindow();
		pTabTest->SelectItem(2);
	}
	else if(strSelName == _T("OptionDemo4"))
	{
		HideCefWindow();
		pTabTest->SelectItem(3);
	}
	else if (strSelName == _T("OptionDemo5"))
	{
		HideCefWindow();
		pTabTest->SelectItem(4);
	}
	//人工翻译
	else if (strSelName == _T("OptionDemo6"))
	{
		CefRefPtr<CefBrowser> browser = g_handler->GetCurrentBrowser();
		if (browser != NULL)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			if (hwnd)
			{
				::ShowWindow(hwnd, SW_SHOW);
				browser->GetMainFrame()->LoadURL(_T("http://f.youdao.com/?keyfrom=dict2.index"));
			}
		}
		pTabTest->SelectItem(5);
	}
	else if (strSelName == _T("OptionDemo7"))
	{
		HideCefWindow();
		pTabTest->SelectItem(6);
	}
	//TabSettings
	if (strSelName == _T("OptSetting1"))
	{
		pTabSettings->SelectItem(0);
	}
	else if (strSelName == _T("OptSetting2"))
	{
		pTabSettings->SelectItem(1);
	}
	else if (strSelName == _T("OptSetting3"))
	{
		pTabSettings->SelectItem(2);
	}
	else if (strSelName == _T("OptSetting4"))
	{
		pTabSettings->SelectItem(3);
	}
	else if (strSelName == _T("OptSetting5"))
	{
		pTabSettings->SelectItem(4);
	}
	else if (strSelName == _T("OptSetting6"))
	{
		pTabSettings->SelectItem(5);
	}
	else if (strSelName == _T("OptSetting7"))
	{
		pTabSettings->SelectItem(6);
	}
}

LRESULT CMainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}


