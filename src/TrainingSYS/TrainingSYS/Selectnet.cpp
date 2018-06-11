// Selectnet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "Selectnet.h"
#include "afxdialogex.h"
#include "TrainingSYSDlg.h"
#include "ts_emf_wnd.h"
#define  PICTURE_NET_LEVEL     "\\res\\picture_com\\"  
// Selectnet �Ի���

IMPLEMENT_DYNAMIC(Selectnet, CDialogEx)

Selectnet::Selectnet(CWnd* pParent /*=NULL*/)
	: CDialogEx(Selectnet::IDD, pParent)
	,m_index(0)
{
	parent = (CTrainingSYSDlg*) ((ButtonDlg *)pParent->GetParent());
	path =    parent->m_path+PICTURE_NET_LEVEL ; 
}

Selectnet::~Selectnet()
{
}

void Selectnet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cb_type);
	DDX_Control(pDX, IDC_BTN_OK, m_btn_ok);
}


BEGIN_MESSAGE_MAP(Selectnet, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_OK, &Selectnet::OnBnClickedBtnOk)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Selectnet ��Ϣ�������


BOOL Selectnet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_btn_ok.SetSkin(path+"play_normal.bmp",path+"play_down.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_mask.bmp",0,0,0);
	//m_index = m_cb_type.GetCurSel();
	m_cb_type.SetCurSel(m_index);
	DrawBmp(path + "comsetting.bmp");
	removechildwnd();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void Selectnet::DrawBmp(CString name)
{
	CString dstname;

	if (name== "")
		return;
	dstname =  name; 
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
	//pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	pDC->StretchBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	memdc.DeleteDC();
	ReleaseDC(pDC);
} 


void Selectnet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� 
	//CDialogEx::OnPaint();
	//	DrawBmp(path + "comsetting.bmp");
	//	removechildwnd();
}


HBRUSH Selectnet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_ST_TITLLE )
		{
			pDC->SetTextColor(RGB(255,255,255));
		}else
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	return hbr;
}

int Selectnet::removechildwnd(void)
{

	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);
	GetDlgItem(IDC_ST_TITLLE)->GetWindowRect(rt);

	//������
	newrt.top   =  parent_rt.top+5;
	newrt.bottom = rt.Height()+5;
	newrt.left   = parent_rt.Width()/2 -rt.Width()/2;
	newrt.right  = newrt.left+ rt.Width();
	GetDlgItem(IDC_ST_TITLLE)->MoveWindow(newrt);

	//�ı�com
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 20;
	newrt.right  = newrt.left  + rt.Width() ;
	GetDlgItem(IDC_ST_SENER)->MoveWindow(newrt);

	//cbcom
	m_cb_type.GetWindowRect(rt);
	newrt.top   =  parent_rt.top+50;
	newrt.bottom = newrt.top + rt.Height() ;
	newrt.left   = 100;
	newrt.right  = newrt.left  + rt.Width() ;
	m_cb_type.MoveWindow(newrt);
	
	m_btn_ok.GetWindowRect(rt);
	newrt.top   =  parent_rt.bottom -rt.Height() -20;
	newrt.bottom = parent_rt.bottom -20 ;
	newrt.left   =  parent_rt.Width()/2-rt.Width()/2;
	newrt.right  =  parent_rt.Width()/2+rt.Width()/2;

	m_btn_ok.MoveWindow(newrt);

	int nScreenWidth, nScreenHeight;  
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);  
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	CRect mainrt,newrct;
	GetWindowRect(mainrt);
	newrct.left = nScreenWidth/2 - mainrt.Width()/2;
	newrct.right += newrct.left + mainrt.Width();
	newrct.top =  nScreenHeight/2 - mainrt.Height()/2;
	newrct.bottom +=  newrct.top +  mainrt.Height();
	this->MoveWindow(newrct);
	return 0;
}
//OK ����
void Selectnet::OnBnClickedBtnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_index = m_cb_type.GetCurSel();

	if (m_index == 0)
	{
		parent->m_pictype  = 1;
	}else if (m_index == 1)
	{
		parent->m_pictype  = 3;
	}else if (m_index == 2)
	{
		parent->m_pictype  = 2;
	}else
	{
		parent->m_pictype  = 4;
	}
	parent->m_pemf_wnd->setEmfType(parent->m_pictype);


	OnOK();
}
BOOL Selectnet::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawBmp(path + "comsetting.bmp");
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void Selectnet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
}
