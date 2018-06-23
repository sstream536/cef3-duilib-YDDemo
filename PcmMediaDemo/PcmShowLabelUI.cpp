#include "StdAfx.h"
#include "PcmShowLabelUI.h"
#include<vector>



CPcmShowLableUI::CPcmShowLableUI()
{

}

CPcmShowLableUI::~CPcmShowLableUI()
{

}

LPCTSTR CPcmShowLableUI::GetClass() const
{
	return PcmShowLableUIClassName;
}

LPVOID CPcmShowLableUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, PcmShowLableUIInterface) == 0){
		return static_cast<CPcmShowLableUI*>(this);
	}
	return CLabelUI::GetInterface(pstrName);
}


void CPcmShowLableUI::DoEvent(DuiLib::TEventUI& event)
{
	CLabelUI::DoEvent(event);
}

void CPcmShowLableUI::PaintStatusImage(HDC hDC)
{
	CLabelUI::PaintStatusImage(hDC);

	std::vector<char> pcm_buffer;
	FILE * file = NULL;
	file = fopen("pcm\\20180601155322.pcm", "rb");

	if (file != NULL) {
		//
		pcm_buffer.clear();
		pcm_buffer.shrink_to_fit();

		fseek(file, 0, SEEK_END);
		unsigned int size_byte = ftell(file);
		fseek(file, 0, SEEK_SET);
		pcm_buffer.resize(size_byte);
		fread(&pcm_buffer[0], size_byte, 1, file);
		fclose(file);
		size_byte /= 2;
		int step = 1, len = size_byte;
		if (size_byte > 20000) {
			len = 20000;
			step = (int)(size_byte / len);
		}
		short * pcm_16 = (short*)(&pcm_buffer[0]);
		std::vector<float> pcm_float;
		pcm_float.resize(20000);
		for (int i = 0, n = 0; n < len; i += step, n++) {
			pcm_float[n] = pcm_16[i];
		}

		float max = pcm_float[0], min = pcm_float[0];
		for (int i = 1; i< pcm_float.size(); i++){
			if (max < pcm_float[i]){
				max = pcm_float[i];
			}
			if (min > pcm_float[i]){
				min = pcm_float[i];
			}
		}
		int w = m_rcItem.right - m_rcItem.left;
		int h = m_rcItem.bottom - m_rcItem.top;
		std::vector<PointF> points;
		float diffVal = max - min;
		for (int i = 0; i < pcm_float.size(); i++){
			points.push_back(PointF(i * w / pcm_float.size(), h - (pcm_float[i] - min) / diffVal * h));
		}

		const DWORD backColor = 0xFFC9C9C9;
		CRenderEngine::DrawColor(hDC, m_rcItem, backColor);
		const DWORD backLineColor = 0xFF0000FF;
		for (int i = 0; i < points.size() - 1; i++){
			RECT rect;
			rect.left = points[i].X;
			rect.top = points[i].Y + m_rcItem.top;
			rect.right = points[i + 1].X;
			rect.bottom = points[i + 1].Y + m_rcItem.top;
			CRenderEngine::DrawLine(hDC, rect, 1, backLineColor);
		}
	}
}

void  CPcmShowLableUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	int i = 0;
}