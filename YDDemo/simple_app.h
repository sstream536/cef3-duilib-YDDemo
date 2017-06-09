#pragma once

#include "include\cef_app.h"

class SimpleApp 
	: public CefApp
	, public CefBrowserProcessHandler 
{
public:
	SimpleApp();
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE{ return this; }

	virtual void OnContextInitialized() OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING(SimpleApp);
};
