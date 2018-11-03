#pragma once

class mCText : public mCWnd
{
	DECLARE_DYNAMIC(mCText)

public:
	mCText();
	virtual ~mCText();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();  
	afx_msg void OnPaint();
};


