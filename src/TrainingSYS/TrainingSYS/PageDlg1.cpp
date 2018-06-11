// PageDlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrainingSYS.h"
#include "TrainingSYSDlg.h"
#include "PageDlg1.h"
#include "afxdialogex.h"
#include "OptionSel.h" 
#include "OptionSelMul.h"
#define  NUM_BTN  3
#define  MYBUTTON_ID        10000
#define  LEFT_BUTTON_OFFSET  310
#define  TOP_BUTTON_OFFSET   30
#define BTN_WIDTH     80
#define BTN_HEIGHT    30
#define BTN_SPACE     150
// PageDlg1 �Ի���

IMPLEMENT_DYNAMIC(PageDlg1, CDialogEx)

PageDlg1::PageDlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(PageDlg1::IDD, pParent)
	,m_index(0)
	,m_timeid(1234)
	,m_isover(false)
	,m_multiple(0)
{
	parent =  (CTrainingSYSDlg *)pParent;
	//��ѫ����·��
	m_pageinf.runpath = parent->m_path;
	//�Ի�����Ҫ����ͼƬ·��
	m_pageinf.pic.path = m_pageinf.runpath+ PICTURE_4_LEVEL;
	m_pageinf.cmd = parent->m_cmd;
}

PageDlg1::~PageDlg1()
{
	m_pageinf.pic.piclist.clear();
	
	vector<OPT_INF_ALL>::iterator iter;  
	for (iter=m_pageinf.opt.moptlist.begin();iter!=m_pageinf.opt.moptlist.end();iter++) 
	{
	   iter->optlist.clear();
	}
	m_pageinf.opt.moptlist.clear();
}

void PageDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, NID_MYBTN_BACK, m_btn_back);
	DDX_Control(pDX, NID_MYBTN_NEXT, m_btn_next);
	DDX_Control(pDX, NID_MYBTN_OK, m_btn_ok);
}

BEGIN_MESSAGE_MAP(PageDlg1, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_BN_CLICKED(NID_MYBTN_OK, OnMybuttonOK)
	ON_BN_CLICKED(NID_MYBTN_NEXT, OnMybuttonNEXT)
	ON_BN_CLICKED(NID_MYBTN_BACK, OnMybuttonBACK)
	ON_WM_TIMER()
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// PageDlg1 ��Ϣ�������


void PageDlg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;  
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(7,92,168));   //����Ϊ��ɫ����
	DrawBmp(m_pageinf.pic.bkpic);
	DrawBmp( m_pageinf.pic.piclist[m_index].bmpname , true, 10);
	
}


// ��ȡxml�б����ͼƬ��Ϣ
int PageDlg1::ReadXMlPictureInfmation(CString cmd)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_PICTUREINF))
		return 1;
	//���Ҹ��ڵ�ʧ��
    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL)
    {
        doc.Clear();
        return 1;
    }
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        CString elemName = elem->Value();
		CString attr;
        attr = elem->Attribute("priority");
		//cmd ����ƥ����ȷ��
        if (cmd == attr)
        {	
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  
				  string elemName = e1->Value();
				  if (elemName== "backpicture")
				  {
					 //���ҵ�����ͼ
					 m_pageinf.pic.bkpic  = e1->Attribute("name");
					 continue;
				  }
				  if (elemName== "picture")
				  {	
					  CString index;
					  PIC_INF pic;
					  pic.bmpname  = e1->Attribute("name");
					  index =e1->Attribute("index");
					  if (index!="")
					  {
						  pic.order = atoi(index.GetBuffer());
					  }
					  if ((!pic.bmpname.IsEmpty()) && (pic.order != 0xff))
					  {
						  m_pageinf.pic.piclist.push_back(pic);
					  }
				  }
			
			}
			m_pageinf.pic.num = m_pageinf.pic.piclist.size();
			doc.Clear();
			return 0;
        } 
    }
    doc.Clear();
	return 1;
}
//��ȡѡ�����
int PageDlg1::ReadXMlOptionInfmation(CString cmd)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_OPTIONTUREINF))
		return 1;
	//���Ҹ��ڵ�ʧ��
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{
		doc.Clear();
		return 1;
	}
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		CString attr;
		attr = elem->Attribute("priority");
		if (cmd == attr)
		{	
			OPT_INF_ALL m_optinf;
			CString mainstr;
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  	
				OPT_INF opt;
		
				CString xlName = e1->Value();
				if (xlName == "mainstyle")
				{  //��ȡ����������
					mainstr  =e1->Attribute("name");
				}else if (xlName == "question")
				{
					for(TiXmlElement* e2 = e1->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
					{
						CString index,optionname;	
						CString elName = e2->Value();
						if (elName == "anwser")
						{
							index =e2->Attribute("index");
							if (index!="")
							{
								//��¼ѡ���
								m_optinf.answer= atoi(index.GetBuffer());
							}
						}else if (elName == "item")
						{
							optionname =e2->Attribute("name");
							if (optionname!="")
							{
								//��¼ѡ������
								m_optinf.option = optionname;
							}
						}else  if (elName == "option")
						{
							opt.optname  = e2->Attribute("name");
							opt.explain  = e2->Attribute("explain");
							index =e2->Attribute("index");
							if (index!="")
							{
								opt.order = atoi(index.GetBuffer());
							}
							if ((!opt.optname.IsEmpty()) && (opt.order != 0xff))
							{
								m_optinf.optlist.push_back(opt);
							}
						}
					}//edn for e2
					m_optinf.num = m_optinf.optlist.size();
					m_pageinf.opt.moptlist.push_back(m_optinf);
					m_optinf.optlist.clear();
				}//els if question
		
			}//end for e1
			m_pageinf.opt.num = m_pageinf.opt.moptlist.size();
			m_pageinf.opt.mainstr = mainstr;
		doc.Clear();
		return 0;
	   } 
	}
	doc.Clear();
	return 1;
}

//��ȡѡ����𰸵�����
int PageDlg1::ReadXMlAnswerName(CString cmd)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(XML_OPTIONTUREINF))
		return 1;
	//���Ҹ��ڵ�ʧ��
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{
		doc.Clear();
		return 1;
	}
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		CString elemName = elem->Value();
		CString attr;
		attr = elem->Attribute("priority");
		if (cmd == attr)
		{	
			//cmd ����ƥ����ȷ��   
			for(TiXmlElement* e1 = elem->FirstChildElement(); e1 != NULL; e1 = e1->NextSiblingElement())
			{  
				CString answername;
				BACK_INF back_inf;
				CString elName = e1->Value();
			    if (elName == "style")
				{
					answername =e1->Attribute("name");
					if (answername!="")
					{
						if (!(parent->FindDataWitchcmd(m_pageinf.cmd)))
						{
							back_inf.name =answername;
							back_inf.num  = 1;
							back_inf.cmd  = m_pageinf.cmd;
							parent->m_bacakinf.push_back(back_inf);
						}
					
						doc.Clear();
						return 0;
					}
				}
			}
			doc.Clear();
			return 1;
		} 
	}
	doc.Clear();
	return 1;
}
BOOL PageDlg1::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	/*ReadXMlTitleName(m_pageinf.cmd);*/
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ReadXMlPictureInfmation(m_pageinf.cmd);
	//m_pageinf.pic.num = m_pageinf.pic.piclist.size();
	ReadXMlOptionInfmation(m_pageinf.cmd);
	//m_pageinf.opt.num = m_pageinf.opt.moptlist.size();
	OnInitButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
byte PageDlg1::CheckHowMangPages()
{
	//ҳ����ͼƬ��������һ��ѡ�
	if (m_pageinf.opt.num)
		return m_pageinf.pic.num + 1;
	else
		return m_pageinf.pic.num ;

}


void PageDlg1::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	// ReMoveButton(); 
}
void PageDlg1::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	 ReMoveButton(); 
}
void PageDlg1::ReMoveButton() 
{
	CRect rect,newrt;
	GetClientRect(&rect);
	if ( GetDlgItem(NID_MYBTN_OK))
	{	
		m_btn_ok.GetWindowRect(&newrt);
		ScreenToClient(&newrt);
		newrt.top	    = rect.bottom-newrt.Height()-TOP_BUTTON_OFFSET;
		newrt.bottom    = rect.bottom-TOP_BUTTON_OFFSET;
		newrt.left	    += LEFT_BUTTON_OFFSET;
		newrt.right     += LEFT_BUTTON_OFFSET;
		m_btn_ok.MoveWindow(&newrt);

	}
	if ( GetDlgItem(NID_MYBTN_BACK))
	{
		m_btn_back.GetWindowRect(&newrt);
		ScreenToClient(&newrt);
		newrt.top	    = rect.bottom-newrt.Height()-TOP_BUTTON_OFFSET;
		newrt.bottom    = rect.bottom-TOP_BUTTON_OFFSET;
		newrt.left	    += LEFT_BUTTON_OFFSET;
		newrt.right     += LEFT_BUTTON_OFFSET;
		m_btn_back.MoveWindow(&newrt);
	}

	if ( GetDlgItem(NID_MYBTN_NEXT))
	{
    	m_btn_next.GetWindowRect(&newrt);
		ScreenToClient(&newrt);
		newrt.top	    = rect.bottom-newrt.Height()-TOP_BUTTON_OFFSET;
		newrt.bottom    = rect.bottom-TOP_BUTTON_OFFSET;
		newrt.left	    += LEFT_BUTTON_OFFSET;
		newrt.right     += LEFT_BUTTON_OFFSET;
		m_btn_next.MoveWindow(&newrt);
	}
	
}
void PageDlg1::OnMybuttonOK()
{
	if(m_pageinf.opt.num == 1)
	{
		OptionSel *dlg =new OptionSel(this);
		int res=dlg->DoModal();
		if (res == IDOK)
		{
			//ReadXMlAnswerName(m_pageinf.cmd);
		}else
		{

		}
		delete dlg;
	}
	else
	{
		
		OptionSelMul *dlg =new OptionSelMul(this);
		int res=dlg->DoModal();
		if (res == IDOK)
		{
			//ReadXMlAnswerName(m_pageinf.cmd);
		}else
		{

		}
		delete dlg;
	
	}
}
void PageDlg1::OnInitButton( )
{
	CString path =m_pageinf.runpath+"\\res\\picture_5\\"; 

	m_btn_ok.SetSkin(path+"ok_normal.bmp",path+"ok_down.bmp",path+"ok_normal.bmp",path+"ok_disable.bmp",path+"ok_normal.bmp",path+"ok_mask.bmp",0,0,0);
	m_btn_back.SetSkin(path+"back_normal.bmp",path+"back_down.bmp",path+"back_normal.bmp",path+"back_disable.bmp",path+"back_normal.bmp",path+"back_mask.bmp",0,0,0);
	m_btn_next.SetSkin(path+"next_normal.bmp",path+"next_down.bmp",path+"next_normal.bmp",path+"next_disable.bmp",path+"next_normal.bmp",path+"next_mask.bmp",0,0,0);
	if (m_pageinf.pic.num <= 1)
	{
		m_btn_back.EnableWindow(false);
		m_btn_next.EnableWindow(false);
		if (m_pageinf.opt.num )
		{
			m_btn_ok.EnableWindow(true);
		}else
			m_btn_ok.EnableWindow(false);
		
	}else if (m_pageinf.pic.num >= 2)
	{
		m_btn_back.EnableWindow(false);
		m_btn_next.EnableWindow(true);
		m_btn_ok.EnableWindow(false);
	}
}//�ܽ�����һҳ��һҳ��˵����page������Ҷ
void PageDlg1::OnMybuttonNEXT()
{
	if (m_isover)return;
	m_index++;
	m_btn_back.EnableWindow(true);
	if (m_pageinf.pic.num - 1 == m_index)
	{	
	   if (m_pageinf.opt.num )m_btn_ok.EnableWindow(true);
	   m_btn_next.EnableWindow(false);
	
	}else
	{
		m_btn_ok.EnableWindow(false);
	}
	m_isover = !m_isover;
	m_dir = false;
	SetTimer(m_timeid,70,NULL);
	

}
void PageDlg1::OnMybuttonBACK()
{
	if (m_isover)return;
	m_index--;
	m_btn_next.EnableWindow(true);
	m_btn_ok.EnableWindow(false);
	if (0 == m_index)
	{
		m_btn_back.EnableWindow(false);
	}

	m_isover = !m_isover;
	m_dir = true;
	SetTimer(m_timeid,70,NULL);
}

void PageDlg1::DrawBmp(CString name)
{
	CString dstname;

	dstname = m_pageinf.pic.path + m_pageinf.pic.piclist[m_index].bmpname;
	if (name== "")return;

	dstname = m_pageinf.pic.path + name; 
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	if (!hbmp)return;
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
	//pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	pDC->StretchBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//pDC->BitBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,SRCCOPY); //��ʾ

	//bitmap.DeleteObject();
	ReleaseDC(pDC);
	memdc.DeleteDC();
} 
void PageDlg1::DrawBmp(CString name ,bool dir,int mul)

{
	CString dstname;
	if (name== "")
		return;

	dstname =   m_pageinf.pic.path + m_pageinf.pic.piclist[m_index].bmpname;
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	if (!hbmp)return;
	CBitmap bitmap;
	bitmap.Attach(hbmp); //����λͼ����  
	CDC *pDC = GetDC();
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(&bitmap);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CRect bmpRC,dstrc;

	::SetBrushOrgEx(::GetDC(this->GetSafeHwnd()),0,0,NULL);
	pDC->SetStretchBltMode(HALFTONE);
	GetClientRect(&bmpRC);
	if (dir==true)
	{
		dstrc.right = bmpRC.Width()/2 + bmp.bmWidth/2;//����������������
		dstrc.left  = bmpRC.Width()/2 + bmp.bmWidth/2 - bmp.bmWidth * mul / 10 ;
		dstrc.top    = bmpRC.top;
		dstrc.bottom = bmpRC.bottom;
		 pDC->StretchBlt(dstrc.left,dstrc.top,dstrc.Width(),dstrc.Height(),&memdc,0,0,dstrc.Width(),dstrc.Height(),SRCCOPY);
	}else
	{
		dstrc.right = bmpRC.Width()/2 - bmp.bmWidth/2 + bmp.bmWidth * mul / 10 ;//����������������
		dstrc.left  = bmpRC.Width()/2 - bmp.bmWidth/2 ;
		dstrc.top    = bmpRC.top;
		dstrc.bottom = bmpRC.bottom;
		pDC->StretchBlt(dstrc.left,dstrc.top,dstrc.Width(),dstrc.Height(),&memdc,bmp.bmWidth - dstrc.Width(),0,dstrc.Width(),dstrc.Height(),SRCCOPY);
	}

	//pDC->StretchBlt(dstrc.left,dstrc.top,dstrc.Width(),dstrc.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//bitmap.DeleteObject();
	ReleaseDC(pDC);
	memdc.DeleteDC();
}

void PageDlg1::OnTimer(UINT_PTR nIDEvent)
{
		if (m_timeid == nIDEvent)
		{		
			m_multiple += 1;
			if (m_multiple >= 11)
			{
				KillTimer(m_timeid);
				m_isover = false;
				m_multiple =0;
			}else
			{
				DrawBmp( m_pageinf.pic.piclist[m_index].bmpname,m_dir,m_multiple);
			}
		}
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


//HBRUSH PageDlg1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  �ڴ˸��� DC ���κ�����
//	CRect   rect;  
//	//GetClientRect(rect);  
//	//dc.FillSolidRect(rect,RGB(7,92,168));   //����Ϊ��ɫ����
//	DrawBmp(m_pageinf.pic.bkpic);
//	DrawBmp( m_pageinf.pic.piclist[m_index].bmpname , true, 10);
//	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
//	return hbr;
//}
