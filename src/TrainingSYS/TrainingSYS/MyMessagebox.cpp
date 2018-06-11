// MyMessagebox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "MyMessagebox.h"
#include "afxdialogex.h"


// MyMessagebox �Ի���

IMPLEMENT_DYNAMIC(MyMessagebox, CDialogEx)

MyMessagebox::MyMessagebox(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyMessagebox::IDD, pParent)
	,bkpicpath("")
	,btnpicpath("")
	,m_return_str("")
	,m_content("")
	,m_tittle("")
{

}

MyMessagebox::~MyMessagebox()
{
}

void MyMessagebox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_KNOW, m_btn_ok);
	DDX_Control(pDX, IDC_STATIC_item, m_item);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_text);
}


BEGIN_MESSAGE_MAP(MyMessagebox, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_KNOW, &MyMessagebox::OnBnClickedBtnKnow)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// MyMessagebox ��Ϣ�������


BOOL MyMessagebox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect   temprect(0,0,280,200);

	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	m_btn_ok.SetSkin(btnpicpath+"know_normal.bmp",btnpicpath+"know_down.bmp",btnpicpath+"know_over.bmp",btnpicpath+"know_normal.bmp",btnpicpath+"know_normal.bmp",btnpicpath+"know_mask.bmp",0,0,0);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	 RemoveWindow();
	 setuserfont(130);
	 m_item.SetWindowText(m_tittle);
	 m_item.SetFont(&m_font);
	 m_text.SetWindowText(m_content);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//OK������Ϣ
void MyMessagebox::OnBnClickedBtnKnow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		CDialogEx::OnOK();

}
void MyMessagebox::DrawBmp(CString strname)
{
	CString dstname;

	if (strname== "")
		return;
	dstname =  strname; 
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	CBitmap bitmap;
	bitmap.Attach(hbmp); //����λͼ����
	CDC *pDC = GetDC();
	CDC memdc;//�����ڴ滭��
	memdc.CreateCompatibleDC(NULL);
	memdc.SelectObject(&bitmap);
	CRect bmpRC;
	this->GetWindowRect(&bmpRC);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//pDC->StretchBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();
	ReleaseDC(pDC);
} 

void MyMessagebox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	//DrawBmp(bkpicpath);
}
void MyMessagebox::SetTheContent(CString content)
{
	m_content =  content;
}
void MyMessagebox::SetTheTitle(CString tittle)
{
	m_tittle =  tittle;
}
void MyMessagebox::SetBkPicture(CString picname)
{
	bkpicpath =  picname;
}
void MyMessagebox::SetbtnPicture(CString picname)
{
	btnpicpath =  picname;
}
CString MyMessagebox::GetReturnValue()
{
	return m_return_str;
}
CString MsgBox(CString tittle,CString content,CString bkpathbmp)
{
	MyMessagebox dlg;
	dlg.SetBkPicture(bkpathbmp);
	dlg.SetTheContent(content);
	dlg.SetTheTitle(tittle);
	dlg.DoModal();
	return dlg.GetReturnValue();
}
CString MsgBox(CString tittle,CString content,CString bkpathbmp,CString btnbmp)
{
	MyMessagebox dlg;

	dlg.SetbtnPicture( btnbmp);
	dlg.SetBkPicture(bkpathbmp);
	dlg.SetTheContent(content);
	dlg.SetTheTitle(tittle);
	dlg.DoModal();
	return dlg.GetReturnValue();
}
HBRUSH MyMessagebox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_item)
		{
			pDC->SetTextColor(RGB(255,255,255));
		}else
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		//pDC->SetTextColor(RGB(255,255,0));//��������Ϊ��ɫ

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	return hbr;
}
void MyMessagebox::RemoveWindow( )
{

	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);
	m_item.GetWindowRect(rt);


	newrt.top   =  parent_rt.top+5;
	newrt.bottom = newrt.top + rt.Height();
	newrt.left   = parent_rt.Width()/2 -rt.Width()/2;
	newrt.right  = newrt.left+ rt.Width();
	m_item.MoveWindow(newrt);

	newrt.top   =  parent_rt.top+35;
	newrt.bottom = parent_rt.bottom - 30 ;
	newrt.left   = 30;
	newrt.right  = parent_rt.Width() - 30;
	m_text.MoveWindow(newrt);
		
	m_btn_ok.GetWindowRect(rt);
	newrt.top   =  parent_rt.bottom -rt.Height() -20;
	newrt.bottom = newrt.top  + rt.Height() ;
	newrt.left   = parent_rt.Width()/2 - rt.Width()/2;
	newrt.right  = newrt.left  + rt.Width();
	m_btn_ok.MoveWindow(newrt);
}
void MyMessagebox::setuserfont(WORD size,CString fontname )
{
	m_font.CreatePointFont(size,fontname);//����15�����壬�����п�
}

BOOL MyMessagebox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawBmp(bkpicpath);
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


//void MyMessagebox::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnMButtonDown(nFlags, point);
//	PostMessage(WM_NCLBUTTONDOWN,
//		HTCAPTION,
//		MAKELPARAM(point.x, point.y));
//}


void MyMessagebox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
}
