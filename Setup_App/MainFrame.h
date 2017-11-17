#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP
#include<string>
#include<thread>
#include<memory>
#include<functional>
class MainFrame : public WindowImplBase
{
public:

	MainFrame();
	~MainFrame();

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
	virtual LPCTSTR MainFrame::GetResourceID() const;
	void OnClick(CControlUI * spender);
	void OnSelChanged(CControlUI * spender);

	void setupEndCallBack();
	void setProcessCallBack(int process,const std::string & info);
	void closeMainFrameCallBack(bool is_close);
protected:

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	void install();
private:
	bool m_is_default_install;
	bool m_is_shortcut;
	bool m_is_agree;
	std::string m_install_path;
	std::shared_ptr<std::thread> m_install_thread;
};

#endif // MAINFRAME_HPP