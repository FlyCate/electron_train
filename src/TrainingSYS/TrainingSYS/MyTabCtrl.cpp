// MyTabCtrl.cpp : ʵ���ļ�
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



// CMyTabCtrl ��Ϣ�������


void CMyTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	//������ˢ
	CBrush      cbr;
	cbr.CreateSolidBrush(RGB(3,46,94));

	//��ȡѡ���������
	char        szTabText[100];
	TC_ITEM     tci;
	memset(szTabText, '\0', sizeof(szTabText));
	tci.mask        = TCIF_TEXT;
	tci.pszText     = szTabText;
	tci.cchTextMax  = sizeof(szTabText)-1;
	GetItem(lpDrawItemStruct->itemID, &tci);
	//���ѡ�����
	CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);
	dc->FillRect(&lpDrawItemStruct->rcItem, &cbr);

	//����ѡ�����
	dc->SetBkColor(RGB(3,46,94));
	dc->SetTextColor(RGB(192,192,192));
	RECT rc;
	rc=lpDrawItemStruct->rcItem;
	rc.top+=1;
	dc->DrawText(tci.pszText,lstrlen(tci.pszText),&rc,DT_CENTER);

}


BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ�ؼ�����

	CRect   rect;
	GetClientRect(&rect);

	//������ˢ
	CBrush   brush;
	brush.CreateSolidBrush(RGB(3,46,94));

	//���ؼ�����
	pDC-> FillRect(&rect,&brush);

	//return CTabCtrl::OnEraseBkgnd(pDC);
	return true;
	return CTabCtrl::OnEraseBkgnd(pDC);
}


