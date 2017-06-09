#include "StdAfx.h"
#include "ButtonTab.h"

CButtonTab::CButtonTab(CPaintManagerUI* ppm)
{
	CDialogBuilder builder;
	CContainerUI* pbtnTab = static_cast<CContainerUI*>(builder.Create(_T("Button.xml"), 0, NULL, ppm));
	if( pbtnTab ) 
	{
		this->Add(pbtnTab);
	}
	else 
	{
		this->RemoveAll();
		return;
	}
}
