#pragma once
#include"..\DuiLib\UIlib.h"
using namespace DuiLib;
class CLoginWnd :public WindowImplBase 
{
public:
	CLoginWnd();
	virtual ~CLoginWnd();
public:
	LPCTSTR GetWindowClassName()const;
	virtual void OnFinalMessage(HWND hwnd);
	virtual void InitWindow();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	void OnClick(CControlUI* pSender);
};

