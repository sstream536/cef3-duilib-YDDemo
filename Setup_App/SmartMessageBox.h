#pragma once
#ifndef SMART_MESSAGE_BOX_HPP
#define SMART_MESSAGE_BOX_HPP
#include"StdAfx.h"
#include<string>
#include<thread>
#include<memory>
#include<functional>

class SmartMessageBox : public WindowImplBase
{
public:

	SmartMessageBox();
	~SmartMessageBox();

public:
	static SmartMessageBox & getInstance(){
		static SmartMessageBox instance;
		return instance;
	}
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

	void OnClick(CControlUI * spender);
	void OnSelChanged(CControlUI * spender);

public:
	void setCallBack(const std::function<void(bool)> & func){
		m_close_main_frame = func;
	}
protected:

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

private:
	std::function<void(bool)> m_close_main_frame;
};

#endif // SMART_MESSAGE_BOX_HPP