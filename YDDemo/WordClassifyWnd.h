#pragma once
#include"..\DuiLib\UIlib.h"
using namespace DuiLib;
class CWordClassifyWnd :public WindowImplBase 
{
public:
	CWordClassifyWnd();
	virtual ~CWordClassifyWnd();
public:
	LPCTSTR GetWindowClassName()const;
	virtual void OnFinalMessage(HWND hwnd);
	virtual void InitWindow();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void SetMainWnd(HWND hWnd);
	void HideWindow();
protected:
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	void OnClick(CControlUI* pSender);
protected:
	CDuiString m_strTransSelect;
	HWND  m_hMianWnd;
};

