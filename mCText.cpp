#include "stdafx.h"
#include "mCText.h"

IMPLEMENT_DYNAMIC(mCText, mCWnd)

mCText::mCText()
{
}
mCText::~mCText()
{
}

BEGIN_MESSAGE_MAP(mCText, mCWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void mCText::PreSubclassWindow()
{
	ModifyStyle(0, SS_NOTIFY); // ÏìÓ¦Êó±ê

	mCWnd::PreSubclassWindow();
}

void mCText::OnPaint()
{
	CPaintDC dc(this);

	DrawBack();

	m_pGraphics->SetSmoothingMode(SmoothingModeHighQuality);

	if(m_jUI["fore"]["type"].asString() == "text")
	{
		CRect crect;
		crect.left = m_jUI["back"]["border"]["left"]["size"].asInt() + m_jUI["back"]["padding"]["left"].asInt();
		crect.right = m_crect.Width() - m_jUI["back"]["border"]["right"]["size"].asInt() - m_jUI["back"]["padding"]["right"].asInt();
		crect.top = m_jUI["back"]["border"]["top"]["size"].asInt() + m_jUI["back"]["padding"]["top"].asInt();
		crect.bottom = m_crect.Height() - m_jUI["back"]["border"]["bottom"]["size"].asInt() - m_jUI["back"]["padding"]["bottom"].asInt();

		UINT uiFormat = DT_SINGLELINE | DT_VCENTER;
		if(m_jUI["fore"]["align"].asString() == "left") uiFormat |= DT_LEFT;
		if(m_jUI["fore"]["align"].asString() == "center") uiFormat |= DT_CENTER;
		if(m_jUI["fore"]["align"].asString() == "right") uiFormat |= DT_RIGHT;

		CFont font;
		font.CreateFont(
			m_jUI["fore"]["FontSize"].asInt() + 10,
			0,
			0,
			0,
			m_jUI["fore"]["bold"].asBool() ? FW_BOLD : FW_NORMAL,
			FALSE,
			m_jUI["fore"]["underline"].asBool() ? TRUE : FALSE,
			0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			L"Arial");

		m_pMemoryDC->SelectObject(&font);
		m_pMemoryDC->SetTextColor(RGB(m_jUI["fore"]["color"]["r"].asInt(), m_jUI["fore"]["color"]["g"].asInt(), m_jUI["fore"]["color"]["b"].asInt()));

		m_pMemoryDC->DrawText(m_sText, crect, uiFormat);

		font.DeleteObject();
	}

	if(m_jUI["fore"]["type"].asString() == "MenuSquare")
	{
		double sinValue = sin(3.1415926 * 45 / 180) * m_iWidth * 8 / 32;
		double cosValue = cos(3.1415926 * 45 / 180) * m_iHeight * 8 / 32;

		float i = m_jUI["PenSize"].asFloat();
		Pen pen(Color(
			m_jUI["fore"]["color"]["r"].asInt(),
			m_jUI["fore"]["color"]["g"].asInt(),
			m_jUI["fore"]["color"]["b"].asInt()),
			m_jUI["fore"]["PenSize"].asFloat());

		m_pGraphics->DrawLine(&pen,
			(float)(m_iWidth * 16 / 32 - sinValue), (float)(m_iHeight * 16 / 32 - cosValue),
			(float)(m_iWidth * 16 / 32 + sinValue), (float)(m_iHeight * 16 / 32 - cosValue)
			);
		m_pGraphics->DrawLine(&pen,
			(float)(m_iWidth * 16 / 32 - sinValue), (float)(m_iHeight * 16 / 32),
			(float)(m_iWidth * 16 / 32 + sinValue), (float)(m_iHeight * 16 / 32)
			);
		m_pGraphics->DrawLine(&pen,
			(float)(m_iWidth * 16 / 32 - sinValue), (float)(m_iHeight * 16 / 32 + cosValue),
			(float)(m_iWidth * 16 / 32 + sinValue), (float)(m_iHeight * 16 / 32 + cosValue)
			);
	}

	m_pGraphics->SetSmoothingMode(SmoothingModeDefault);

	ShowMemoryDC(&dc);
}
