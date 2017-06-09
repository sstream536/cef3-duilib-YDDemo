//
#pragma once

class CTransSelectWnd;
class CWordClassifyWnd;
class CWordSortWnd;
class CWordManagerWnd;
class CMiniModeWnd;
class CMainFrame : public WindowImplBase
{
public:
	CMainFrame();
	virtual ~CMainFrame();
public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void FirstLoadCef();
	void HideCefWindow();
	HWND GetMainWnd(){ return this->m_hWnd; }
protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	//
	void OnSelChanged(CControlUI* pSender);
	void OnClick(CControlUI * pSender);
	//cef
	void AdjustCefWindow();
	void UpdateTransString(int nNum);
	//create wnd
	void ShowTransSelectFrame();
	void ShowWordClassifyFrame();
	void ShowWordSortFrame();
	void ShowWordManagerFrame();
	void HideLayoutFrame();
	void ShowMiniModeFrame();
private:
	BOOL     m_bIsInit;
	CTransSelectWnd *m_pTransSelectFrame;
	CWordClassifyWnd *m_pWordClassifyFrame;
	CWordSortWnd *m_pWordSortFrame;
	CWordManagerWnd *m_pWordManagerFrame;
	CMiniModeWnd *m_pMiniModeFrame;
};