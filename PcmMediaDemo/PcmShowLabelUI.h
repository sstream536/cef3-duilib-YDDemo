#ifndef _PCM_SHOW_LABEL_UI_
#define _PCM_SHOW_LABEL_UI_

#include "UIlib.h"
#include "Control\UILabel.h"
using namespace DuiLib;

const TCHAR PcmShowLableUIClassName[] = _T("PcmShowLableUI");
const TCHAR PcmShowLableUIInterface[] = _T("PcmShowLable");


class CPcmShowLableUI : public CLabelUI
{
public:
	CPcmShowLableUI();
	~CPcmShowLableUI();
protected:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void DoEvent(DuiLib::TEventUI& event);
	virtual void PaintStatusImage(HDC hDC);
	virtual void DoPaint(HDC hDC, const RECT& rcPaint);
};



#endif // _PCM_SHOW_LABEL_UI_