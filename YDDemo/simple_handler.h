
#pragma once
#include "include\cef_client.h"
#include <list>

class SimpleHandler 
	: public CefClient
	, public CefDisplayHandler
	, public CefLifeSpanHandler
{
public:
	SimpleHandler();
	virtual ~SimpleHandler();
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE
	{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,const CefString& title) OVERRIDE;
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	CefRefPtr<CefBrowser> GetCurrentBrowser();

private:
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	BrowserList browser_list_;

private:
	IMPLEMENT_REFCOUNTING(SimpleHandler);
};