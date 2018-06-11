// OptionSel.cpp : 实现文件
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "OptionSel.h"
#include "afxdialogex.h"
#include "PageDlg1.h"
#include "MyMessagebox.h"
#define IDC_MYRADIO1 10004
#define IDC_MYRADIO2 IDC_MYRADIO1+1
#define IDC_MYRADIO3 IDC_MYRADIO2+1
#define IDC_MYRADIO4 IDC_MYRADIO3+1
#define IDC_MYRADIO5 IDC_MYRADIO4+1
#define IDC_MYRADIO6 IDC_MYRADIO5+1
#define LEFT_POS  15 //选项左侧坐标
#define TOP_POS   65 //第一个选项的顶部坐标
#define ITEM_STEP_HIGH 30 //所有选项之间的间隔
#define TEXT_HIGH 30 //文本框的高度
#define TEXT_HIGH_OFFSET 3 //文本框的相对于 选项高度偏移
#define TEXT_LEFT_OFFSET 25 //文本框的相对于 左侧偏移
// OptionSel 对话框

IMPLEMENT_DYNAMIC(OptionSel, CDialogEx)

OptionSel::OptionSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(OptionSel::IDD, pParent)
	, m_SelRadio(-1)
	,m_num(0)
	,m_btnradio_1(0)
	,m_btnradio_2(0)
	,m_btnradio_3(0)
	,m_btnradio_4(0)
	,m_btnradio_5(0)
	,m_btnradio_6(0)
{
	parent =  (PageDlg1 *)pParent;
	path =parent->m_pageinf.runpath+PICTURE_5_LEVEL ;
}

OptionSel::~OptionSel()
{
	if (m_btnradio_1)
	{
		delete m_btnradio_1;
		m_btnradio_1 =0;
	}
	if (m_btnradio_2)
	{
		delete m_btnradio_2;
		m_btnradio_2 =0;
	}
	if (m_btnradio_3)
	{
		delete m_btnradio_3;
		m_btnradio_3 =0;
	}
	if (m_btnradio_4)
	{
		delete m_btnradio_4;
		m_btnradio_4 =0;
	}
	if (m_btnradio_5)
	{
		delete m_btnradio_5;
		m_btnradio_5 =0;
	}
	if (m_btnradio_6)
	{
		delete m_btnradio_6;
		m_btnradio_6 =0;
	}
}

void OptionSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_ITEM1, m_txt_1);
	DDX_Control(pDX, IDC_ST_ITEM2, m_txt_2);
	DDX_Control(pDX, IDC_ST_ITEM3, m_txt_3);
	DDX_Control(pDX, IDC_ST_ITEM4, m_txt_4);
	DDX_Control(pDX, IDC_ST_ITEM5, m_txt_5);
	DDX_Control(pDX, IDC_BUTTON1, m_next);
	DDX_Control(pDX, IDC_OPTION_NAME, m_optname);
	DDX_Control(pDX, IDC_ST_ITEM6, m_txt_6);
}


BEGIN_MESSAGE_MAP(OptionSel, CDialogEx)

	ON_BN_CLICKED(IDC_MYRADIO1, &OptionSel::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_MYRADIO2, &OptionSel::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_MYRADIO3, &OptionSel::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_MYRADIO4, &OptionSel::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_MYRADIO5, &OptionSel::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_MYRADIO6, &OptionSel::OnBnClickedRadio6)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &OptionSel::OnBnClickedButton1)
END_MESSAGE_MAP()


// OptionSel 消息处理程序


void OptionSel::OnBnClickedRadio1()
{
	m_SelRadio=0;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSel::OnBnClickedRadio2()
{	
	m_SelRadio=1;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSel::OnBnClickedRadio3()
{
	m_SelRadio=2;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSel::OnBnClickedRadio4()
{
	m_SelRadio=3;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSel::OnBnClickedRadio5()
{
	m_SelRadio=4;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}
void OptionSel::OnBnClickedRadio6()
{
	m_SelRadio=5;
	if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
	{
		CString explian;
		explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
		MsgBox("",explian, path+"error.bmp",path);
	}else
	{
		MsgBox("","", path+"right.bmp",path);
	}
}


BOOL OptionSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	// TODO:  在此添加额外的初始化
	CRect   temprect(0,0,360,280);

	 CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	 DrawBmp(path+"option.bmp");
	// EnableToolTips(TRUE);  
	// m_Mytip.Create(this); 
	 m_next.SetSkin(path+"play_normal.bmp",path+"play_down.bmp",path+"play_over.bmp",path+"play_normal.bmp",path+"play_normal.bmp",path+"play_mask.bmp",0,0,0);
	       
	 NewRadioWithQuestion( parent->m_pageinf.opt.moptlist[m_num].num);
	 m_optname.SetWindowText(parent->m_pageinf.opt.mainstr);
	 SetIteminfmation(m_num);
	// CeateTipInfmation( m_num);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void OptionSel::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}
void OptionSel::CeateTipInfmation(byte num)
{
	
	if (parent->m_pageinf.opt.moptlist[num].num > 0)
	{
			//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM1),parent->m_pageinf.opt.moptlist[num].optlist[0].explain);
			m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO1),parent->m_pageinf.opt.moptlist[num].optlist[0].explain); 
	}
	if (parent->m_pageinf.opt.moptlist[num].num>1)
	{
		m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO2),parent->m_pageinf.opt.moptlist[num].optlist[1].explain);
		//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM2),parent->m_pageinf.opt.moptlist[num].optlist[1].explain);
	}
	if (parent->m_pageinf.opt.moptlist[num].num>2)
	{
	    m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO3),parent->m_pageinf.opt.moptlist[num].optlist[2].explain); 
		//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM3),parent->m_pageinf.opt.moptlist[num].optlist[2].explain);
	}
		 
	if (parent->m_pageinf.opt.moptlist[num].num>3)
	{
		m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO4),parent->m_pageinf.opt.moptlist[num].optlist[3].explain);
		//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM4),parent->m_pageinf.opt.moptlist[num].optlist[3].explain);
	}
		
	if (parent->m_pageinf.opt.moptlist[num].num>4)
	{
		m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO5),parent->m_pageinf.opt.moptlist[num].optlist[4].explain);
		//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM5),parent->m_pageinf.opt.moptlist[num].optlist[4].explain);
	}
	if (parent->m_pageinf.opt.moptlist[num].num>5)
	{
		m_Mytip.AddTool( GetDlgItem(IDC_MYRADIO6),parent->m_pageinf.opt.moptlist[num].optlist[5].explain);
		//m_Mytip.AddTool(GetDlgItem(IDC_ST_ITEM5),parent->m_pageinf.opt.moptlist[num].optlist[4].explain);
	}
	m_Mytip.SetDelayTime(500 ); //设置延迟
	m_Mytip.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	m_Mytip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_Mytip.Activate(TRUE); //设置是否启用提示
}


BOOL OptionSel::PreTranslateMessage(MSG* pMsg)
{

	//if(pMsg->message==WM_MOUSEMOVE )
	//	m_Mytip.RelayEvent(pMsg);
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}
void OptionSel::DrawBmp(CString strname)
{
	CString dstname;
	if (strname.IsEmpty())
	{
		return;
	}
	dstname = strname;
	//if (m_index >= m_pageinf.pic.piclist.size())
	//	return;	
	//dstname = m_pageinf.pic.path + m_pageinf.pic.piclist[m_index].bmpname;
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 

	CBitmap bitmap;
	bitmap.Attach(hbmp); //关联位图对象  
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
	//pDC->BitBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,SRCCOPY); //显示
	memdc.DeleteDC();
	ReleaseDC(pDC);
		
} 

void OptionSel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//DrawBmp(path+"option.bmp");
}


HBRUSH OptionSel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor == CTLCOLOR_STATIC  )
	{
		if (pWnd->GetDlgCtrlID() == IDC_OPTION_NAME)
		{
			pDC->SetTextColor(RGB(255,255,255));
		}else
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		//pDC->SetTextColor(RGB(255,255,0));//设置字体为黄色

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	} 
	return hbr;
}
//设置用户字体
void OptionSel::setuserfont()
{
	m_font.CreatePointFont(90,"黑体");//代表15号字体，华文行楷
}
void OptionSel::setuserfont(WORD size,CString fontname )
{
	if (!m_font.CreatePointFont(size,fontname))//代表15号字体，华文行楷
	{
		printf_s("创建字体失败.\n");
	}
}

BOOL OptionSel::OnEraseBkgnd(CDC* pDC)
{
	DrawBmp(path+"option.bmp");
	return true;
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialogEx::OnEraseBkgnd(pDC);
}
void OptionSel::NewRadioWithQuestion(byte num)
{
	if (num == 0)return ;
	if (num >= 7)num =6;

	m_btnradio_1 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO1, CRect(LEFT_POS,TOP_POS+0*ITEM_STEP_HIGH,200,100), WS_GROUP );
	m_btnradio_2 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO2, CRect(LEFT_POS,TOP_POS+1*ITEM_STEP_HIGH,200,150), 0 );
	m_btnradio_3 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO3, CRect(LEFT_POS,TOP_POS+2*ITEM_STEP_HIGH,200,200), 0 );
	m_btnradio_4 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO4, CRect(LEFT_POS,TOP_POS+3*ITEM_STEP_HIGH,200,250), 0 );
	m_btnradio_5 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO5, CRect(LEFT_POS,TOP_POS+4*ITEM_STEP_HIGH,200,300), 0 );
	m_btnradio_6 = (CxSkinButton*)NewMyRadio( IDC_MYRADIO6, CRect(LEFT_POS,TOP_POS+5*ITEM_STEP_HIGH,200,300), 0 );

	CRect rt,newrt,parent_rt;
	this->GetClientRect(parent_rt);
	m_txt_1.GetWindowRect(rt);

	newrt.left = LEFT_POS + TEXT_LEFT_OFFSET ;
	newrt.right = parent_rt.Width()-30;

    newrt.top =TOP_POS+0*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
	newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_1.MoveWindow(newrt);

	newrt.top = TOP_POS+1*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
	newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_2.MoveWindow(newrt);

	newrt.top = TOP_POS+2*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
    newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_3.MoveWindow(newrt);

	newrt.top = TOP_POS+3*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
    newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_4.MoveWindow(newrt);

	newrt.top = TOP_POS+4*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
    newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_5.MoveWindow(newrt);

	newrt.top = TOP_POS+5*ITEM_STEP_HIGH+TEXT_HIGH_OFFSET;
	newrt.bottom =  newrt.top +TEXT_HIGH;
	m_txt_6.MoveWindow(newrt);

	//移动按键
	m_next.GetWindowRect(rt);

	newrt.top    =   parent_rt.bottom - rt.Height()-10;
	newrt.bottom =   parent_rt.bottom -10;
	newrt.left   =  parent_rt.Width()/2-rt.Width()/2;
	newrt.right  =  parent_rt.Width()/2+rt.Width()/2;
	m_next.MoveWindow(newrt);

	//移动标题
	m_optname.GetWindowRect(rt);

	newrt.top    =   parent_rt.top+10;
	newrt.bottom =   parent_rt.top+rt.Height()+10;
	newrt.left   =   parent_rt.Width()/2 - rt.Width()/2;
	newrt.right  =   parent_rt.Width()/2 + rt.Width()/2;
	m_optname.MoveWindow(newrt);

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

	m_btnradio_1->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	m_btnradio_2->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	m_btnradio_3->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	m_btnradio_4->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	m_btnradio_5->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	m_btnradio_6->SetSkin(path+"check_normal.bmp",path+"check_down.bmp",path+"check_over.bmp",path+"check_normal.bmp",path+"check_normal.bmp",path+"check_mask.bmp",0,0,0);
	//m_btnradio_1->SetToolTipText("Radio1");
	ChangbtnVisable(m_num);
}
CxSkinButton* OptionSel::NewMyRadio(int nID,CRect rect,int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString( nID ); //取按钮标题
	CxSkinButton *p_Radio = new CxSkinButton();
	ASSERT_VALID(p_Radio);
	p_Radio->Create( m_Caption, WS_CHILD | WS_VISIBLE | nStyle | WS_TABSTOP | BS_AUTORADIOBUTTON, rect, this, nID ); //创建按钮
	return p_Radio;
}
//设置当前选项卡信息 num 当前是第几道选择题
void  OptionSel::SetIteminfmation(byte num)
{   
	setuserfont( 140,"宋体");
	m_optname.SetWindowText(	parent->m_pageinf.opt.mainstr);
	m_optname.SetFont(&m_font);
	if (parent->m_pageinf.opt.moptlist[num].num > 0)
		m_txt_1.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[0].optname);
	if (parent->m_pageinf.opt.moptlist[num].num > 1)
		m_txt_2.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[1].optname);
	if (parent->m_pageinf.opt.moptlist[num].num > 2)
		m_txt_3.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[2].optname);
	if (parent->m_pageinf.opt.moptlist[num].num > 3)
		m_txt_4.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[3].optname);
	if (parent->m_pageinf.opt.moptlist[num].num > 4)
		m_txt_5.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[4].optname);
	if (parent->m_pageinf.opt.moptlist[num].num > 5)
		m_txt_6.SetWindowText(parent->m_pageinf.opt.moptlist[num].optlist[5].optname);


}
//点击下一道提
void OptionSel::OnBnClickedButton1()
{
	if (m_SelRadio < 0)
	{
	    MsgBox("","请先选择题目答案", path+"error.bmp",path);
		return;
	}else
	{
		if (m_SelRadio != parent->m_pageinf.opt.moptlist[m_num].answer)
		{
			CString explian;
			//explian = parent->m_pageinf.opt.moptlist[m_num].optlist[m_SelRadio].explain;
			MsgBox("","请先选择题目答案", path+"error.bmp",path);
			return;
		}else
		{
				CDialogEx::OnOK();
		}
	}
}

void  OptionSel::ChangbtnVisable(byte num)
{
	if (parent->m_pageinf.opt.moptlist[num].num < 6 )
	{ 
		m_btnradio_6->ShowWindow(FALSE);
		m_txt_6.ShowWindow(FALSE);
	}
	if (parent->m_pageinf.opt.moptlist[num].num < 5 )
	{ 
		m_btnradio_5->ShowWindow(FALSE);
		m_txt_5.ShowWindow(FALSE);
	}
	if (parent->m_pageinf.opt.moptlist[num].num < 4) 
	{
		m_btnradio_4->ShowWindow(FALSE);
		m_txt_4.ShowWindow(FALSE);
	}
	if (parent->m_pageinf.opt.moptlist[num].num < 3)
	{
		m_btnradio_3->ShowWindow(FALSE);
		m_txt_3.ShowWindow(FALSE);
	}	
	if (parent->m_pageinf.opt.moptlist[num].num < 2) 
	{
		m_btnradio_2->ShowWindow(FALSE);
		m_txt_2.ShowWindow(FALSE);
	}	
	if (parent->m_pageinf.opt.moptlist[num].num < 1)
	{
		m_btnradio_1->ShowWindow(FALSE);
		m_txt_1.ShowWindow(FALSE);
	}
	m_btnradio_1->SetCheck(FALSE);
	m_btnradio_2->SetCheck(FALSE);
	m_btnradio_3->SetCheck(FALSE);
	m_btnradio_4->SetCheck(FALSE);
	m_btnradio_5->SetCheck(FALSE);
	m_btnradio_6->SetCheck(FALSE);
}