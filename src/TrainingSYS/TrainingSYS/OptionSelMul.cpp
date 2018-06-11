// OptionSelMul.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "OptionSelMul.h"
#include "afxdialogex.h"
#include "MyMessagebox.h"
#define IDC_MMYRADIO1 10010
#define MAIN_TITTLE_BAR      35 //������
#define SUBJECT_1_ROW_Y 45  //ѡ������Ŀ1 2 x������� 
#define SUBJECT_2_ROW_Y 145 //ѡ������Ŀ3 4 x�������  
#define SUBJECT_1_COL_X 65 //ѡ������Ŀ1 3 y�������  
#define SUBJECT_2_COL_X 235 //ѡ������Ŀ2 4 y�������  

#define OPTION_1_ROW_Y  70   //ѡ��ѡ��1 2 x������� 
#define OPTION_2_ROW_Y 170 //ѡ��ѡ��3 4 x�������  
#define OPTION_1_COL_X 40 //ѡ��ѡ��1 3 y�������  
#define OPTION_2_COL_X 210 //ѡ��ѡ��2 4 y�������  

#define RADIO_1_ROW_Y    OPTION_1_ROW_Y
#define RADIO_2_ROW_Y    OPTION_2_ROW_Y
#define RADIO_1_COL_X 10 //RADIOѡ��ѡ��1 3 y�������  
#define RADIO_2_COL_X 180 //READIOѡ��ѡ��2 4 y�������  

#define RADIO_STEP_HIGH 25
#define TEXT_STEP_HIGH  25  //�ı���߶�
#define TEXT_WIDTH      120 //�ı�����
#define TEXT_HEIGH      30  //�ı���߶�

#define RADIO_WIDTH      20 //�ı�����
#define RADIO_HEIGH      20  //�ı���߶�


// OptionSelMul �Ի���

IMPLEMENT_DYNAMIC(OptionSelMul, CDialogEx)
#define  PICTURE_5_LEVEL_MUL     "\\res\\picture_5\\"  
OptionSelMul::OptionSelMul(CWnd* pParent /*=NULL*/)
	: CDialogEx(OptionSelMul::IDD, pParent)
	,path("")
	, m_group_0_sel(255)
	, m_group_1_sel(255)
	, m_group_2_sel(255)
	, m_group_3_sel(255)


{
	memset(m_radio,0,sizeof(m_radio));
	memset(	m_optglag,1,sizeof(m_optglag));

	parent =  (PageDlg1 *)pParent;

	path =parent->m_pageinf.runpath+PICTURE_5_LEVEL_MUL ;
}

OptionSelMul::~OptionSelMul()
{
	for (int i=0;i<12;i++)
	{
		if (m_radio[i] !=0)
		{
			delete m_radio[i];
			 m_radio[i] =0;
		}
	}
}

void OptionSelMul::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_next);
}


BEGIN_MESSAGE_MAP(OptionSelMul, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MMYRADIO1+0, &OptionSelMul::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_MMYRADIO1+1, &OptionSelMul::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_MMYRADIO1+2, &OptionSelMul::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_MMYRADIO1+3, &OptionSelMul::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_MMYRADIO1+4, &OptionSelMul::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_MMYRADIO1+5, &OptionSelMul::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_MMYRADIO1+6, &OptionSelMul::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_MMYRADIO1+7, &OptionSelMul::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_MMYRADIO1+8, &OptionSelMul::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_MMYRADIO1+9, &OptionSelMul::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_MMYRADIO1+10, &OptionSelMul::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_MMYRADIO1+11, &OptionSelMul::OnBnClickedRadio12)

	ON_BN_CLICKED(IDC_BUTTON1, &OptionSelMul::OnBnClickedButton1)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// OptionSelMul ��Ϣ�������
void OptionSelMul::NewRadioWithQuestion(byte num)
{
	if (num == 0)return ;
	if (num >= 13)num =12;
	byte i=0;
	//����12��radio�ؼ�
	for (i=0;i<12;i++)
	//num 0-3�ڼ���ѡ���� style 0 ��Ŀ 1 ѡ��RADIO 2 �ı���ѡ�� optnum 0 -2 ѡ�
	{   
		RECT rt = calcwndrect(i/3  ,2, i%3);
		if (i%3 ==0)
			m_radio[i] = (CxSkinButton*)NewMyRadio( IDC_MMYRADIO1+i, &rt, WS_GROUP );
		else
		    m_radio[i] = (CxSkinButton*)NewMyRadio( IDC_MMYRADIO1+i,  &rt, 0 );
	}
	
	//m_btnradio_1 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO1, CRect(LEFT_POS,TOP_POS+0*ITEM_STEP_HIGH,200,100), WS_GROUP );

}
CxSkinButton* OptionSelMul::NewMyRadio(int nID,CRect rect,int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString( nID ); //ȡ��ť����
	CxSkinButton *p_Radio = new CxSkinButton();
	ASSERT_VALID(p_Radio);
	p_Radio->Create( m_Caption, WS_CHILD | WS_VISIBLE | nStyle | WS_TABSTOP | BS_AUTORADIOBUTTON, rect, this, nID ); //������ť
	return p_Radio;
}
//num 0-3�ڼ���ѡ���� style 0 ��Ŀ 1 ѡ��RADIO 2 �ı���ѡ�� optnum 0 -2 ѡ�
RECT OptionSelMul::calcwndrect(byte num ,byte style,byte optnum)
{
   RECT rt;
   if (style==0)//��Ŀ
   {
	   rt.top  = ( (num==0) || (num==1) ) ? SUBJECT_1_ROW_Y : SUBJECT_2_ROW_Y;
	   rt.left = ( (num==0) || (num==2) ) ? SUBJECT_1_COL_X : SUBJECT_2_COL_X;
	   rt.right =  rt.left + TEXT_WIDTH;
	   rt.bottom  =  rt.top + TEXT_HEIGH;
   }else    if (style==2)//radio
   {    rt.top  = ( (num==0) || (num==1) ) ? RADIO_1_ROW_Y + optnum*RADIO_STEP_HIGH : RADIO_2_ROW_Y + optnum*RADIO_STEP_HIGH;
	    rt.left = ( (num==0) || (num==2) ) ? RADIO_1_COL_X : RADIO_2_COL_X;
		rt.right  =  rt.left + RADIO_WIDTH;
		rt.bottom =  rt.top  + RADIO_HEIGH;
   }else if (style==1)//ѡ���ı�
   {
	   rt.top  = ( (num==0) || (num==1) ) ? OPTION_1_ROW_Y + optnum*TEXT_STEP_HIGH : OPTION_2_ROW_Y + optnum*TEXT_STEP_HIGH;
	   rt.left = ( (num==0) || (num==2) ) ? OPTION_1_COL_X : OPTION_2_COL_X;
	   rt.right  =  rt.left + TEXT_WIDTH;
	   rt.bottom =  rt.top  + TEXT_HEIGH;
   }else
   {
	   rt.top  = 0;
	   rt.left =  0;
	   rt.right  =  rt.left + TEXT_WIDTH;
	   rt.bottom =  rt.top  + TEXT_HEIGH;
   }
   return rt;
}
void OptionSelMul::RemoveChildWND(void)
{
	byte i=0;
	RECT rt;
	CStatic *wnd;
	for( i = 0 ; i < 16 ; i++)
	{
		if (i%4 == 0)
			 rt = calcwndrect(i/4  ,0, i%3);
		else
			 rt = calcwndrect(i/4  ,1, i%4-1);
		 wnd = GetDlgYithNum( i);
		 if (wnd)
		 { 
			 wnd->MoveWindow(&rt);
		 }
	}

	CRect rt1,newrt,parent_rt;
	this->GetClientRect(parent_rt);

	//�ƶ�����
	m_btn_next.GetWindowRect(rt1);

	newrt.top    =   parent_rt.bottom - rt1.Height()-10;
	newrt.bottom =   parent_rt.bottom -10;
	newrt.left   =  parent_rt.Width()/2 - rt1.Width()/2;
	newrt.right  =  parent_rt.Width()/2 + rt1.Width()/2;
	m_btn_next.MoveWindow(newrt);

	//�ƶ�����
	((CStatic*)GetDlgItem(IDC_ST_MAINNAME))->GetWindowRect(rt1);
	newrt.top    =   parent_rt.top+10;
	newrt.bottom =   parent_rt.top+rt1.Height()+10;
	newrt.left   =   parent_rt.Width()/2 - rt1.Width()/2;
	newrt.right  =   parent_rt.Width()/2 + rt1.Width()/2;
	((CStatic*)GetDlgItem(IDC_ST_MAINNAME))->MoveWindow(newrt);

	int nScreenWidth, nScreenHeight;  
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);  
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect mainrt,newrct;
	GetWindowRect(mainrt);
	newrct.left = nScreenWidth/2 - mainrt.Width()/2;
	newrct.right += newrct.left + mainrt.Width();
	newrct.top =  nScreenHeight/2 - mainrt.Height()/2;
	newrct.bottom =  newrct.top +  mainrt.Height();
	this->MoveWindow(newrct);
}

void  OptionSelMul::Initdlgchildwnd(void)
{
	for (int i=0;i<12;i++)
	{
		m_radio[i]->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	}

}
CStatic * OptionSelMul::GetDlgYithNum(byte num)
{
	byte i=0;

	CStatic *wnd;
	switch (num)
	{
	case 0: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX1);break;
	case 1: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX2);break;
	case 2: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX3);break;
	case 3: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX4);break;
	case 4: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX5);break;
	case 5: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX6);break;
	case 6: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX7);break;
	case 7: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX8);break;
	case 8: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX9);break;
	case 9: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX10);break;
	case 10: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX11);break;
	case 11: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX12);break;
	case 12: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX13);break;
	case 13: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX14);break;
	case 14: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX15);break;
	case 15: wnd = (CStatic*)GetDlgItem(IDC_STATIC_TX16);break;

	default :wnd=0;break;
	}
	return wnd;
	
	
}
BOOL OptionSelMul::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect   temprect(0,0,360,280);
	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	 m_btn_next.SetSkin(path+"play_normal.bmp",path+"play_down.bmp",path+"play_over.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_mask.bmp",0,0,0);
	NewRadioWithQuestion(12);
	Initdlgchildwnd();
	RemoveChildWND();
	IintOptionContentuser();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void OptionSelMul::DrawBmp(CString strname)
{
	CString dstname;
	if (strname.IsEmpty())
	{
		return;
	}
	dstname = strname;

	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 

	CBitmap bitmap;
	bitmap.Attach(hbmp); //����λͼ����  
	CDC *pDC = GetDC();
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(&bitmap);
	BITMAP bmp;

	bitmap.GetBitmap(&bmp);
	CRect bmpRC;
	this->GetWindowRect(&bmpRC);
	::SetBrushOrgEx(::GetDC(this->GetSafeHwnd()),0,0,NULL);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//pDC->BitBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,SRCCOPY); //��ʾ
	memdc.DeleteDC();
	ReleaseDC(pDC);
} 

void OptionSelMul::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//DrawBmp(path+"option.bmp");

}


HBRUSH OptionSelMul::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_ST_MAINNAME)
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
	void OptionSelMul::setuserfont(WORD size,CString fontname )
{
	m_font.CreatePointFont(size,fontname);//����15�����壬�����п�
}



void OptionSelMul::IintOptionContentuser(void)
{
	//���ô����
	//setuserfont( 180,"����");
					

	m_fnt.CreatePointFont(140,"����");//����15�����壬�����п�
	((CStatic*)GetDlgItem(IDC_ST_MAINNAME))->SetWindowText(	parent->m_pageinf.opt.mainstr);
	((CStatic*)GetDlgItem(IDC_ST_MAINNAME))->SetFont(&m_fnt);

	//m_font.DeleteObject();  
	setuserfont( 120,"����");

	//�޸�text1��text12���ַ���
	byte i=0;
	CString str;
	CStatic *wnd;
	for (i=0;i<parent->m_pageinf.opt.num;i++)
	{
		 wnd = (CStatic *)GetDlgYithNum(i*4);
		str  = parent->m_pageinf.opt.moptlist[i].option;
	    wnd->SetWindowText(str);
		wnd->SetFont(&m_font);
		if ( parent->m_pageinf.opt.moptlist[i].num > 0 )
		{
			wnd = (CStatic *) GetDlgYithNum(i*4+1);
			str  = parent->m_pageinf.opt.moptlist[i].optlist[0].optname;
			wnd->SetWindowText(str);
		}
		if ( parent->m_pageinf.opt.moptlist[i].num > 1 )
		{
			wnd =  (CStatic *)GetDlgYithNum(i*4+2);
			str  = parent->m_pageinf.opt.moptlist[i].optlist[1].optname;
			wnd->SetWindowText(str);
		}
		if ( parent->m_pageinf.opt.moptlist[i].num > 2 )
		{
			wnd = (CStatic *) GetDlgYithNum(i*4+3);
			str  = parent->m_pageinf.opt.moptlist[i].optlist[2].optname;
			wnd->SetWindowText(str);
		}
	}
	 HideUNnedWND();

}
void OptionSelMul::HideUNnedWND(void)
{
	byte i=0;
	CString str;
	CStatic *wnd;

	if(parent->m_pageinf.opt.num < 4)
	{
		m_optglag[3] = 0;
		for (i=12;i<12+4;i++)
		{
			wnd = (CStatic *)GetDlgYithNum(i);
			wnd->ShowWindow(FALSE);
		}
		for (i=9;i<9+3;i++)
		{
			m_radio[i]->ShowWindow(FALSE);
		}
	
	}
	if(parent->m_pageinf.opt.num < 3)
	{
		m_optglag[2] = 0;
		for (i=8;i<8+4;i++)
		{
			wnd = (CStatic *)GetDlgYithNum(i);
			wnd->ShowWindow(FALSE);
		}
		for (i=6;i<6+3;i++)
		{
			m_radio[i]->ShowWindow(FALSE);
		}
	}
	if(parent->m_pageinf.opt.num < 2)
	{
		m_optglag[1] = 0;
		for (i=4;i<4+4;i++)
		{
			wnd = (CStatic *)GetDlgYithNum(i);
			wnd->ShowWindow(FALSE);
		}
		for (i=3;i<3+3;i++)
		{
			m_radio[i]->ShowWindow(FALSE);
		}
	}
	if(parent->m_pageinf.opt.num < 1)
	{
		m_optglag[0] = 0;
		for (i=0;i<0+4;i++)
		{
			wnd = (CStatic *)GetDlgYithNum(i);
			wnd->ShowWindow(FALSE);
		}
		for (i=0;i<0+3;i++)
		{
			m_radio[i]->ShowWindow(FALSE);
		}
	}
	//����ѡ��ͶԺ�
	for (i=0;i< parent->m_pageinf.opt.num ;i++)
	{
		if ( parent->m_pageinf.opt.moptlist[i].num <3  )
		{
			wnd = (CStatic *) GetDlgYithNum(i*4+3);
			m_radio[i*3+2]->ShowWindow(FALSE);
			wnd->ShowWindow(FALSE);
		}
		if ( parent->m_pageinf.opt.moptlist[i].num < 2 )
		{
			wnd =  (CStatic *)GetDlgYithNum(i*4+2);
			m_radio[i*3+1]->ShowWindow(FALSE);
			wnd->ShowWindow(FALSE);
		}
		if ( parent->m_pageinf.opt.moptlist[i].num < 1 )
		{
			wnd = (CStatic *) GetDlgYithNum(i*4+1);
			m_radio[i*3+0]->ShowWindow(FALSE);
			wnd->ShowWindow(FALSE);
		}
	}
	
}
// OptionSel ��Ϣ�������


void OptionSelMul::OnBnClickedRadio1()
{
	m_group_0_sel=0;
	if (m_group_0_sel != parent->m_pageinf.opt.moptlist[0].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[0].optlist[m_group_0_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio2()
{	
	m_group_0_sel=1;
	if (m_group_0_sel != parent->m_pageinf.opt.moptlist[0].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[0].optlist[m_group_0_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio3()
{
	m_group_0_sel=2;
	if (m_group_0_sel != parent->m_pageinf.opt.moptlist[0].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[0].optlist[m_group_0_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}


void OptionSelMul::OnBnClickedRadio4()
{
	m_group_1_sel=0;
	if (m_group_1_sel != parent->m_pageinf.opt.moptlist[1].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[1].optlist[m_group_1_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio5()
{
	m_group_1_sel=1;
	if (m_group_1_sel != parent->m_pageinf.opt.moptlist[1].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[1].optlist[m_group_1_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio6()
{
	m_group_1_sel=2;
	if (m_group_1_sel != parent->m_pageinf.opt.moptlist[1].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[1].optlist[m_group_1_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}

void OptionSelMul::OnBnClickedRadio7()
{
	m_group_2_sel=0;
	if (m_group_2_sel != parent->m_pageinf.opt.moptlist[2].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[2].optlist[m_group_2_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio8()
{	
	m_group_2_sel=1;
	if (m_group_2_sel != parent->m_pageinf.opt.moptlist[2].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[2].optlist[m_group_2_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio9()
{
	m_group_2_sel=2;
	if (m_group_2_sel != parent->m_pageinf.opt.moptlist[2].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[2].optlist[m_group_2_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}

void OptionSelMul::OnBnClickedRadio10()
{
	m_group_3_sel=0;
	if (m_group_3_sel != parent->m_pageinf.opt.moptlist[3].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[3].optlist[m_group_3_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio11()
{
	m_group_3_sel=1;
	if (m_group_3_sel != parent->m_pageinf.opt.moptlist[3].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[3].optlist[m_group_3_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSelMul::OnBnClickedRadio12()
{
	m_group_3_sel=2;
	if (m_group_3_sel != parent->m_pageinf.opt.moptlist[3].answer)
	{  
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[3].optlist[m_group_3_sel].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
//�û����ȷ���󰴼�
void OptionSelMul::OnBnClickedButton1()
{
	
	if ( m_optglag[0] == 1 )
	{
		if (m_group_0_sel == 255)
		{  
			MsgBox("","����ѡ����Ŀ\"1\"��", path+"error.bmp",path);
		    return;
		}
	} 
	if ( m_optglag[1] == 1 )
	{
		if (m_group_1_sel == 255)
		{  
			MsgBox("","����ѡ����Ŀ\"2\"��", path+"error.bmp",path);
			return;
		}
	} 
	if ( m_optglag[2] == 1 )
	{
		if (m_group_2_sel == 255)
		{  
			MsgBox("","����ѡ����Ŀ\"3\"��", path+"error.bmp",path);
			return;
		}
	} 
	if ( m_optglag[3] == 1 )
	{
		if (m_group_3_sel == 255)
		{  
			MsgBox("","����ѡ����Ŀ\"4\"��", path+"error.bmp",path);
			return;
		}
	}


		if ( m_optglag[0] == 1 )
		{
			if (m_group_0_sel != parent->m_pageinf.opt.moptlist[0].answer)
			{  
				//CString explian;
				//explian = parent->m_pageinf.opt.moptlist[0].optlist[m_group_0_sel].explain;
				MsgBox("","��Ŀ\"1\"�𰸴���", path+"error.bmp",path);
				return;
			}
		}
		if ( m_optglag[1] == 1 )
		{
			if (m_group_1_sel != parent->m_pageinf.opt.moptlist[1].answer)
			{  
				//CString explian;
			//	explian = parent->m_pageinf.opt.moptlist[1].optlist[m_group_1_sel].explain;
				MsgBox("","��Ŀ\"2\"�𰸴���", path+"error.bmp",path);
				return;
			}
		}
		if ( m_optglag[2] == 1 )
		{
			if (m_group_2_sel != parent->m_pageinf.opt.moptlist[2].answer)
			{  
				//CString explian;
				//explian = parent->m_pageinf.opt.moptlist[2].optlist[m_group_2_sel].explain;
				MsgBox("","��Ŀ\"3\"�𰸴���", path+"error.bmp",path);
				return;
			}
		}
		if ( m_optglag[3] == 1 )
		{
			if (m_group_3_sel != parent->m_pageinf.opt.moptlist[3].answer)
			{  
				//CString explian;
				//explian = parent->m_pageinf.opt.moptlist[3].optlist[m_group_3_sel].explain;
				MsgBox("","��Ŀ\"4\"�𰸴���", path+"error.bmp",path);
				return;
			}
		}
		
		CDialogEx::OnOK();
		
}

BOOL OptionSelMul::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawBmp(path+"option.bmp");
	//RemoveChildWND();
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void OptionSelMul::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
}
