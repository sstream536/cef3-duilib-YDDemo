#include "simple_handler.h"
#include "simple_app.h"

#include "include/wrapper/cef_helpers.h"

SimpleHandler::SimpleHandler()
{

}

SimpleHandler::~SimpleHandler() 
{

}

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
	const CefString& title)
{
	CEF_REQUIRE_UI_THREAD();
	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	SetWindowText( hwnd, title.ToWString().c_str() );
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	browser_list_.push_back(browser);
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	BrowserList::iterator bit = browser_list_.begin();
	for (; bit != browser_list_.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			browser_list_.erase(bit);
			break;
		}
	}

	if (browser_list_.empty()) {
		// All browser windows have closed. Quit the application message loop.
		CefQuitMessageLoop();
	}
}

CefRefPtr<CefBrowser> SimpleHandler::GetCurrentBrowser()
{
	CEF_REQUIRE_UI_THREAD();
	if (browser_list_.size() > 0)
	{
		BrowserList::iterator bit = browser_list_.begin();
		if (bit != browser_list_.end())
		{
			return *bit;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}