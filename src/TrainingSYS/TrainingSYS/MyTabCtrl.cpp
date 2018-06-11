// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序


void CMyTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	//创建画刷
	CBrush      cbr;
	cbr.CreateSolidBrush(RGB(3,46,94));

	//获取选项卡文字内容
	char        szTabText[100];
	TC_ITEM     tci;
	memset(szTabText, '\0', sizeof(szTabText));
	tci.mask        = TCIF_TEXT;
	tci.pszText     = szTabText;
	tci.cchTextMax  = sizeof(szTabText)-1;
	GetItem(lpDrawItemStruct->itemID, &tci);
	//填充选项卡背景
	CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);
	dc->FillRect(&lpDrawItemStruct->rcItem, &cbr);

	//绘制选项卡文字
	dc->SetBkColor(RGB(3,46,94));
	dc->SetTextColor(RGB(192,192,192));
	RECT rc;
	rc=lpDrawItemStruct->rcItem;
	rc.top+=1;
	dc->DrawText(tci.pszText,lstrlen(tci.pszText),&rc,DT_CENTER);

}


BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获取控件矩形

	CRect   rect;
	GetClientRect(&rect);

	//创建画刷
	CBrush   brush;
	brush.CreateSolidBrush(RGB(3,46,94));

	//填充控件背景
	pDC-> FillRect(&rect,&brush);

	//return CTabCtrl::OnEraseBkgnd(pDC);
	return true;
	return CTabCtrl::OnEraseBkgnd(pDC);
}


