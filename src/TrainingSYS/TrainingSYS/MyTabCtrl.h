#pragma once

#include "xSkinButton.h"
// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


